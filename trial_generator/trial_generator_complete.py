import os
import random
import json
import numpy as np

# ---------------------------
# Configurazione (modifica questi valori)
# ---------------------------
audio_channels = [6,7,26,25]            # usa solo i canali qui elencati
target_slaves = ["SLAVE1", "SLAVE2"]    # usa solo gli slave qui elencati
visual_dir = "visual cues led matrices"  # cartella con JSON pattern visivi

# ISI: estremo inferiore (incluso) e superiore (escluso) per avere, ad es., 2000 valori
isi_val_extremes = (1000, 1500)
isi_values = np.arange(isi_val_extremes[0], isi_val_extremes[1] + 1)
N_repeats = len(isi_values)

# Parametri stimoli
onset = 0
offset = 50  # ms
freq = 5000
d_c = 50
cycle_offset = 0

# Se True non salva i JSON dei trial (utile per debug)
DRY_RUN = False

# Directory di salvataggio
save_dir = os.path.expanduser("~/Desktop/MultisensorySetup/PsychophysicalInterface-master/testing_trials")

# ---------------------------
# Carica i pattern visivi (JSON già pronti)
# Ogni file .json nella cartella può contenere una lista di entries, ognuna con
# {"CONTROLLER_TARGET": "SLAVE1", "PIXELS": [[x,y,r,g,b], ...]}
# ---------------------------
pixel_data_entries = []
if os.path.exists(visual_dir):
    for fname in os.listdir(visual_dir):
        if not fname.lower().endswith('.json'):
            continue
        file_path = os.path.join(visual_dir, fname)
        try:
            with open(file_path, 'r', encoding='utf-8') as jf:
                data = json.load(jf)
                if isinstance(data, list):
                    for entry in data:
                        if isinstance(entry, dict) and 'CONTROLLER_TARGET' in entry and 'PIXELS' in entry:
                            pixel_data_entries.append(entry)
                        else:
                            print(f"Skipped malformed entry in {file_path}: {entry}")
                else:
                    print(f"Skipped non-list JSON in {file_path}")
        except Exception as e:
            print(f"Failed to load visual JSON {file_path}: {e}")
else:
    print(f"Warning: visual directory '{visual_dir}' not found.")

# Costruisci mappa slave -> [(PIXELS, SIDE), ...]
pixels_map = {}
for entry in pixel_data_entries:
    tgt = entry.get('CONTROLLER_TARGET')
    pixels = entry.get('PIXELS')
    side = entry.get('SIDE')  # Leggi il SIDE dal JSON
    pixels_map.setdefault(tgt, []).append((pixels, side))

print(f"Loaded {len(pixel_data_entries)} visual entries. CONTROLLER_TARGETs: {sorted(pixels_map.keys())}")

# Mappa di coerenza: (SLAVE, SIDE) -> [canali audio coerenti]
coherence_map = {
    ('SLAVE1', 'LEFT'): [6],      # SLAVE1 sinistra -> canale 6
    ('SLAVE1', 'RIGHT'): [26],     # SLAVE1 destra -> canale 26
    ('SLAVE2', 'LEFT'): [25],     # SLAVE2 sinistra -> canale 25
    ('SLAVE2', 'RIGHT'): [7],     # SLAVE2 destra -> canale 7
}

# ---------------------------
# Costruzione combinazioni
# - A: una combinazione per ciascun canale in audio_channels
# - V: per ciascun slave in target_slaves e per ogni immagine assegnata a quello slave
# - AV: prodotto cartesiano: per ogni canale audio, per ogni slave configurato, per ogni immagine assegnata a quello slave
# ---------------------------
trial_combinations = []

# A
for chan in audio_channels:
    trial_combinations.append(("A", chan, None, None))

# V
for slave in target_slaves:
    patterns = pixels_map.get(slave, [])
    if not patterns:
        print(f"Info: nessun pattern visivo trovato per {slave}; non verranno creati V-only per questo slave.")
        continue
    for pixels, side in patterns:
        trial_combinations.append(("V", None, slave, pixels, side))

# AV - Applica vincolo di coerenza: solo accoppiamenti (chan, slave, side) coerenti
for slave in target_slaves:
    patterns = pixels_map.get(slave, [])
    if not patterns:
        print(f"Info: nessun pattern visivo per {slave}; saltando AV per questo slave.")
        continue
    for pixels, side in patterns:
        # Trova i canali audio coerenti con (slave, side)
        coherent_chans = coherence_map.get((slave, side), [])
        for chan in coherent_chans:
            if chan in audio_channels:
                trial_combinations.append(("AV", chan, slave, pixels, side))

# Conteggi e aspettativa
from collections import Counter
counts = Counter([c[0] for c in trial_combinations])
count_A = counts.get('A', 0)
count_V = counts.get('V', 0)
count_AV = counts.get('AV', 0)
print(f"Combinazioni: A={count_A}, V={count_V}, AV={count_AV}")
print(f"Numero ISI (N_repeats) = {N_repeats}")
print(f"Numero totale di trial atteso = ({count_A} + {count_V} + {count_AV}) * {N_repeats} = {(count_A + count_V + count_AV) * N_repeats}")

# --- Preparazione cartelle (svuota) ---
def clear_folder(folder_path):
    if os.path.exists(folder_path):
        for filename in os.listdir(folder_path):
            file_path = os.path.join(folder_path, filename)
            if os.path.isfile(file_path):
                os.remove(file_path)

for sub in ["A", "V", "AV", "Mixed"]:
    d = os.path.join(save_dir, sub)
    os.makedirs(d, exist_ok=True)
    clear_folder(d)

# --- Generazione dei trial: per ogni combinazione, per ogni ISI ---
trial_counter = 1
for comb in trial_combinations:
    if len(comb) == 4:
        trial_type, audio_chan, target_slave, pixels = comb
        side = None
    else:
        trial_type, audio_chan, target_slave, pixels, side = comb
    # se vuoi ordine casuale degli ISI usa permutation, altrimenti iterali in ordine
    for isi in np.random.permutation(isi_values):
        trial_duration = offset + int(isi)
        trial = {
            "NAME": None,
            "DURATION": trial_duration,
            "AUDITORY_STIMULI": [],
            "VISUAL_STIMULI": [],
            "TRIAL_TYPE": trial_type
        }

        name_parts = [f"{trial_counter:04d}_trial", trial_type]

        if trial_type in ["A", "AV"]:
            trial["AUDITORY_STIMULI"] = [{
                "CHANNEL": audio_chan,
                "ONSET": onset,
                "OFFSET": offset,
                "FREQUENCY": freq,
                "DUTY_CYCLE": d_c,
                "CYCLE_OFFSET": cycle_offset
            }]
            direction = "right" if audio_chan in [7, 26] else "left"
            name_parts.append(direction)

        if trial_type in ["V", "AV"]:
            trial["VISUAL_STIMULI"] = [{
                "CONTROLLER_TARGET": target_slave,
                "ONSET": onset,
                "OFFSET": offset,
                "PIXELS": pixels
            }]
            name_parts.append(target_slave)

        name_parts.append(str(trial_duration))
        trial["NAME"] = "_".join(name_parts)

        if not DRY_RUN:
            # salva in sottocartella del tipo
            type_dir = os.path.join(save_dir, trial_type)
            os.makedirs(type_dir, exist_ok=True)
            with open(os.path.join(type_dir, f"{trial['NAME']}.json"), 'w', encoding='utf-8') as f:
                json.dump(trial, f, ensure_ascii=False, indent=2)

            # salva anche in Mixed
            mixed_dir = os.path.join(save_dir, "Mixed")
            os.makedirs(mixed_dir, exist_ok=True)
            with open(os.path.join(mixed_dir, f"{trial['NAME']}.json"), 'w', encoding='utf-8') as f:
                json.dump(trial, f, ensure_ascii=False, indent=2)

        trial_counter += 1

print(f"Completed. Generated {trial_counter-1} trials (DRY_RUN={DRY_RUN}).")
