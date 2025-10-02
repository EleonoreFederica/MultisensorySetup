
import os
import random
import shutil
import json
import datetime

# Try to use tkinter dialogs for folder name input; fall back to console input if unavailable
try:
    import tkinter as tk
    from tkinter import simpledialog, messagebox
    TK_AVAILABLE = True
except Exception:
    TK_AVAILABLE = False

# === FILTRI MODALITÀ TRIAL ===
ESTRAI_A = True  # True per estrarre solo trial A
ESTRAI_V = True  # True per estrarre solo trial V
ESTRAI_AV = True   # True per estrarre solo trial AV

# === CONFIGURAZIONE ===
COMBINATIONS_PATH = r"C:\Users\Acer\Desktop\MultisensorySetup\PsychophysicalInterface-master\testing_trials\Mixed"  # Modifica questo path se necessario
N_RANDOM_TRIALS = 100  # Numero di trial da estrarre casualmente
# Base folder where new subset folders will be created (parent is testing_trials)
BASE_TESTING_TRIALS_DIR = r"C:\Users\Acer\Desktop\MultisensorySetup\PsychophysicalInterface-master\testing_trials\blocks"

# === FUNZIONE PRINCIPALE ===
def _ask_for_folder_name(initial='random_subset'):
    """Ask the user for a folder name using a dialog (preferred) or console input.
    Returns a safe folder name (non-empty). If user cancels, returns None.
    """
    if TK_AVAILABLE:
        root = tk.Tk()
        root.withdraw()
        name = simpledialog.askstring('Nuova cartella subset', 'Inserisci il nome della nuova cartella per il subset:', initialvalue=initial)
        root.destroy()
        return name
    else:
        try:
            name = input(f"Inserisci il nome della nuova cartella per il subset (invio = '{initial}'): ")
            return name.strip() or initial
        except Exception:
            return None


def estrai_random_subset(slave_targets=None):
    # Chiedi all'utente il nome della cartella dove salvare il subset (sotto testing_trials)
    default_name = 'random_subset'
    folder_name = _ask_for_folder_name(initial=default_name)
    if not folder_name:
        # Se annulla o nulla, usa un nome con timestamp per evitare collisioni
        ts = datetime.datetime.now().strftime('%Y%m%d_%H%M%S')
        folder_name = f"{default_name}_{ts}"

    target_dir = os.path.join(BASE_TESTING_TRIALS_DIR, folder_name)

    # Se esiste già, chiedi se cancellare i file al suo interno (se possibile con GUI)
    if os.path.exists(target_dir):
        clear = False
        if TK_AVAILABLE:
            root = tk.Tk()
            root.withdraw()
            clear = messagebox.askyesno('Cartella esistente', f"La cartella '{folder_name}' esiste già. Vuoi svuotarla e riscriverla?")
            root.destroy()
        else:
            ans = input(f"La cartella '{target_dir}' esiste già. Vuoi svuotarla e riscriverla? (s/N): ")
            clear = ans.strip().lower().startswith('s')

        if clear:
            for f in os.listdir(target_dir):
                file_path = os.path.join(target_dir, f)
                if os.path.isfile(file_path):
                    os.remove(file_path)
        else:
            # Se l'utente non vuole svuotarla, crea una nuova cartella con timestamp
            ts = datetime.datetime.now().strftime('%Y%m%d_%H%M%S')
            folder_name = f"{folder_name}_{ts}"
            target_dir = os.path.join(BASE_TESTING_TRIALS_DIR, folder_name)
            os.makedirs(target_dir, exist_ok=True)
    else:
        os.makedirs(target_dir, exist_ok=True)

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
        dst = os.path.join(target_dir, trial_file)
        shutil.copy2(src, dst)
    print(f"Estratti {N_RANDOM_TRIALS} trial randomici in {target_dir}")

if __name__ == "__main__":
    # Esempio: estrai solo trial con SLAVE1 oppure SLAVE2 (modifica la lista come vuoi)
    # estrai_random_subset(slave_targets=["SLAVE1"])  # Solo SLAVE1
    # estrai_random_subset(slave_targets=["SLAVE2"])  # Solo SLAVE2
    estrai_random_subset(slave_targets=["SLAVE1", "SLAVE2"])  # Entrambi
    # estrai_random_subset()  # Nessun filtro, comportamento originale
