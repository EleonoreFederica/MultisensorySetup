
import os
import random
import shutil
import json

# === FILTRI MODALITÀ TRIAL ===
ESTRAI_A = True  # True per estrarre solo trial A
ESTRAI_V = False   # True per estrarre solo trial V
ESTRAI_AV = False   # True per estrarre solo trial AV

# === CONFIGURAZIONE ===
COMBINATIONS_PATH = r"C:\Users\Acer\Desktop\ingegneria\tesi magistrale\Codici\PsychophysicalInterface-master\testing_trials\Mixed"  # Modifica questo path se necessario
N_RANDOM_TRIALS = 10  # Numero di trial da estrarre casualmente
RANDOM_SUBSET_DIR = os.path.join(r"C:\Users\Acer\Desktop\ingegneria\tesi magistrale\Codici\PsychophysicalInterface-master\testing_trials", "random_subset")

# === FUNZIONE PRINCIPALE ===
def estrai_random_subset(slave_targets=None):
    # Svuota la cartella random_subset se esiste già
    if os.path.exists(RANDOM_SUBSET_DIR):
        for f in os.listdir(RANDOM_SUBSET_DIR):
            file_path = os.path.join(RANDOM_SUBSET_DIR, f)
            if os.path.isfile(file_path):
                os.remove(file_path)
    else:
        os.makedirs(RANDOM_SUBSET_DIR)

    all_trials = [f for f in os.listdir(COMBINATIONS_PATH) if f.lower().endswith('.json')]
    print(f"Numero di file .json trovati in '{COMBINATIONS_PATH}': {len(all_trials)}")

    # === FILTRO MODALITÀ TRIAL SUL NOME DEL FILE ===
    filtered_trials = []
    for trial_file in all_trials:
        if ESTRAI_A and "_A_" in trial_file:
            filtered_trials.append(trial_file)
        elif ESTRAI_V and "_V_" in trial_file:
            filtered_trials.append(trial_file)
        elif ESTRAI_AV and "_AV_" in trial_file:
            filtered_trials.append(trial_file)
    if ESTRAI_A or ESTRAI_V or ESTRAI_AV:
        all_trials = filtered_trials
        print(f"Numero di file dopo filtro modalità: {len(all_trials)}")

    if slave_targets is not None:
        slave_targets = set(s.upper() for s in slave_targets)
        filtered_trials_slave = []
        for trial_file in all_trials:
            trial_path = os.path.join(COMBINATIONS_PATH, trial_file)
            try:
                with open(trial_path, 'r', encoding='utf-8') as f:
                    data = json.load(f)
                visual_stimuli = data.get('VISUAL_STIMULI', [])
                if not visual_stimuli:
                    # Nessuno stimolo visivo: includi sempre
                    filtered_trials_slave.append(trial_file)
                else:
                    slaves_in_trial = {stim.get('CONTROLLER_TARGET', '').upper() for stim in visual_stimuli if 'CONTROLLER_TARGET' in stim}
                    if slaves_in_trial & slave_targets:
                        filtered_trials_slave.append(trial_file)
            except Exception as e:
                print(f"Errore nella lettura di {trial_file}: {e}")
        all_trials = filtered_trials_slave
        print(f"Numero di file dopo filtro SLAVE {slave_targets} (solo su trial con stimolo visivo): {len(all_trials)}")

    if len(all_trials) < N_RANDOM_TRIALS:
        raise ValueError("Non ci sono abbastanza trial per l'estrazione randomica.")
    random_subset = random.sample(all_trials, N_RANDOM_TRIALS)
    for trial_file in random_subset:
        src = os.path.join(COMBINATIONS_PATH, trial_file)
        dst = os.path.join(RANDOM_SUBSET_DIR, trial_file)
        shutil.copy2(src, dst)
    print(f"Estratti {N_RANDOM_TRIALS} trial randomici in {RANDOM_SUBSET_DIR}")

if __name__ == "__main__":
    # Esempio: estrai solo trial con SLAVE1 oppure SLAVE2 (modifica la lista come vuoi)
    # estrai_random_subset(slave_targets=["SLAVE1"])  # Solo SLAVE1
    # estrai_random_subset(slave_targets=["SLAVE2"])  # Solo SLAVE2
    estrai_random_subset(slave_targets=["SLAVE1", "SLAVE2"])  # Entrambi
    # estrai_random_subset()  # Nessun filtro, comportamento originale
