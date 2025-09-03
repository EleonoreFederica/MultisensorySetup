import os
import random
import json
import numpy as np
from PIL import Image

# === Parametri generali ===
N_repeats = 500
onset = 0
offset = 50  # ms
freq = 5000  # Hz
d_c = 50
cycle_offset = 0
isi_val_extremes = (1000, 1500)  # ms
isi_val = np.random.randint(isi_val_extremes[0], isi_val_extremes[1] + 1, size=isi_val_extremes[1] - isi_val_extremes[0] + 1)

trial_counter = 1  # per contare da 001 a 7000

trial_combinations = []

audio_channels = [6, 7]  # 6 dx / 7 sx
target_slaves = ["SLAVE1", "SLAVE2"]
image_files = [
    "visual cues led matrices/left_matrix.png",
    "visual cues led matrices/right_matrix.png"
]

# === Carica pixel immagini ===
def load_pixels(image_path):
    img = Image.open(image_path).convert("RGB")
    img = img.resize((128, 64))
    pixels = []
    for y in range(img.height):
        for x in range(img.width):
            r, g, b = img.getpixel((x, y))
            if not (r == 0 and g == 0 and b == 0):
                pixels.append([x, y, r, g, b])
    return pixels

pixel_data = [load_pixels(path) for path in image_files]

# Stampa la lunghezza e i primi 5 pixel di ciascuna immagine per verifica
print('pixel_data[0] (left_matrix): lunghezza =', len(pixel_data[0]))
print('Esempio pixel:', pixel_data[0][:5])
print('pixel_data[1] (right_matrix): lunghezza =', len(pixel_data[1]))
print('Esempio pixel:', pixel_data[1][:5])

# === Costruisci tutte le 14 combinazioni ===

# A - solo audio
for chan in audio_channels:
    trial_combinations.append(("A", chan, None, None))

# V - solo visivo
for slave in target_slaves:
    for pix in pixel_data:
        trial_combinations.append(("V", None, slave, pix))

# AV - combinato
for chan in audio_channels:
    for slave in target_slaves:
        for pix in pixel_data:
            trial_combinations.append(("AV", chan, slave, pix))

# === Directory salvataggio ===
save_dir = os.path.expanduser("~/Desktop/ingegneria/tesi magistrale/Codici/PsychophysicalInterface-master/testing_trials")
os.makedirs(save_dir, exist_ok=True)

# === Generazione 14 × 500 trial ===
for comb in trial_combinations:
    trial_type, audio_chan, target_slave, pixels = comb
    for _ in range(N_repeats):
        isi = np.random.randint(isi_val_extremes[0], isi_val_extremes[1] + 1)
        trial_duration = offset + isi

        trial = {
            "DURATION": trial_duration,
            "AUDITORY_STIMULI": [],
            "VISUAL_STIMULI": [],
            "TRIAL_TYPE": trial_type
        }

        name_parts = [f"{trial_counter:04d}_trial", trial_type]

        if trial_type in ["A", "AV"]:
            direction = "right" if audio_chan == 6 else "left"
            trial["AUDITORY_STIMULI"] = [{
                "CHANNEL": audio_chan,
                "ONSET": onset,
                "OFFSET": offset,
                "FREQUENCY": freq,
                "DUTY_CYCLE": d_c,
                "CYCLE_OFFSET": cycle_offset
            }]
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

        # Salvataggio in sottocartelle per tipo trial
        type_dir = os.path.join(save_dir, trial_type)
        os.makedirs(type_dir, exist_ok=True)
        file_path_type = os.path.join(type_dir, f"{trial['NAME']}.json")
        with open(file_path_type, 'w', encoding='utf-8') as f:
            json.dump(trial, f, ensure_ascii=False, indent=2)

        # Salvataggio in cartella Mixed
        mixed_dir = os.path.join(save_dir, "Mixed")
        os.makedirs(mixed_dir, exist_ok=True)
        file_path_mixed = os.path.join(mixed_dir, f"{trial['NAME']}.json")
        with open(file_path_mixed, 'w', encoding='utf-8') as f:
            json.dump(trial, f, ensure_ascii=False, indent=2)

        trial_counter += 1
