import sys
import json
from PyQt5.QtWidgets import (
    QApplication, QWidget, QVBoxLayout, QHBoxLayout, QLabel, QScrollArea,
    QPushButton, QSpinBox, QGridLayout, QColorDialog, QComboBox, QFrame, QFileDialog, QTextEdit)
from PyQt5.QtGui import QPainter, QColor, QPen, QMouseEvent
from PyQt5.QtCore import Qt, QPoint

MATRIX_SIZE = 64
PIXEL_SIZE = 8  # each cell will be 15x15 pixels

COLORI_BASE = {
    'Rosso': QColor(255, 0, 0),
    'Giallo': QColor(255, 255, 0),
    'Blu': QColor(0, 0, 255),
    'Verde': QColor(0, 255, 0),
    'Bianco': QColor(255, 255, 255),
    'Nero': QColor(0, 0, 0)
}

FORME = ['Nessuna', 'Cerchio', 'Quadrato', 'Triangolo', 'Croce']

class MatrixWidget(QFrame):
    def __init__(self, name):
        super().__init__()
        self.name = name
        self.setFixedSize(MATRIX_SIZE * PIXEL_SIZE, MATRIX_SIZE * PIXEL_SIZE)
        self.pixels = [[QColor(0, 0, 0) for _ in range(MATRIX_SIZE)] for _ in range(MATRIX_SIZE)]
        self.current_color = QColor(255, 0, 0)  # default to red
        self.current_figure = 'Nessuna'
        self.figure_dim = 3
        self.setMouseTracking(True)
        self.preview_pos = None  # (x, y) per la preview della figura

    def mouseMoveEvent(self, event):
        x = event.x() // PIXEL_SIZE
        y = event.y() // PIXEL_SIZE
        if 0 <= x < MATRIX_SIZE and 0 <= y < MATRIX_SIZE:
            self.preview_pos = (x, y)
            self.update()
        else:
            self.preview_pos = None
            self.update()

    def set_color(self, color):
        self.current_color = color

    def set_figure(self, figure):
        self.current_figure = figure

    def set_figure_dim(self, dim):
        self.figure_dim = dim

    def paintEvent(self, event):
        painter = QPainter(self)
        # Disegna i pixel
        for y in range(MATRIX_SIZE):
            for x in range(MATRIX_SIZE):
                painter.fillRect(x * PIXEL_SIZE, y * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, self.pixels[y][x])
        # Disegna la preview della figura sotto il mouse
        if self.preview_pos and self.current_figure != 'Nessuna':
            self.draw_shape_preview(painter, *self.preview_pos)
        # Disegna la griglia
        grid_pen = QPen(QColor(50, 50, 50))
        grid_pen.setWidth(1)
        painter.setPen(grid_pen)
        for i in range(MATRIX_SIZE + 1):
            painter.drawLine(i * PIXEL_SIZE, 0, i * PIXEL_SIZE, MATRIX_SIZE * PIXEL_SIZE)
            painter.drawLine(0, i * PIXEL_SIZE, MATRIX_SIZE * PIXEL_SIZE, i * PIXEL_SIZE)
        # Disegna una X centrale sui 9 pixel centrali
        center = MATRIX_SIZE // 2
        x0 = (center - 1) * PIXEL_SIZE
        y0 = (center - 1) * PIXEL_SIZE
        x1 = (center + 1) * PIXEL_SIZE + PIXEL_SIZE - 1
        y1 = (center + 1) * PIXEL_SIZE + PIXEL_SIZE - 1
        x_pen = QPen(QColor(200, 200, 200))
        x_pen.setWidth(2)
        painter.setPen(x_pen)
        painter.drawLine(x0, y0, x1, y1)
        painter.drawLine(x0, y1, x1, y0)

    def leaveEvent(self, event):
        self.preview_pos = None
        self.update()

    def draw_shape_preview(self, painter, cx, cy):
        # Disegna la figura selezionata in trasparenza
        color = QColor(self.current_color)
        color.setAlpha(120)
        pen = QPen(color)
        brush = color
        painter.setPen(pen)
        painter.setBrush(brush)
        r = self.figure_dim // 2
        if self.current_figure == 'Cerchio':
            for j in range(max(cy - r, 0), min(cy + r + 1, MATRIX_SIZE)):
                dx = int((r ** 2 - (j - cy) ** 2) ** 0.5)
                for i in range(max(cx - dx, 0), min(cx + dx + 1, MATRIX_SIZE)):
                    painter.fillRect(i * PIXEL_SIZE, j * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color)
        elif self.current_figure == 'Quadrato':
            for i in range(cx - r, cx + r + 1):
                for j in range(cy - r, cy + r + 1):
                    if 0 <= i < MATRIX_SIZE and 0 <= j < MATRIX_SIZE:
                        painter.fillRect(i * PIXEL_SIZE, j * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color)
        elif self.current_figure == 'Triangolo':
            h = self.figure_dim
            for row in range(h):
                y = cy - h // 2 + row
                if 0 <= y < MATRIX_SIZE:
                    half_base = row * (h // 2) // max(h - 1, 1)
                    for x in range(cx - half_base, cx + half_base + 1):
                        if 0 <= x < MATRIX_SIZE:
                            painter.fillRect(x * PIXEL_SIZE, y * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color)
        elif self.current_figure == 'Croce':
            size = self.figure_dim
            half = size // 2
            # Linea orizzontale
            for i in range(-half, half + 1):
                x = cx + i
                if 0 <= x < MATRIX_SIZE and 0 <= cy < MATRIX_SIZE:
                    painter.fillRect(x * PIXEL_SIZE, cy * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color)
            # Linea verticale
            for j in range(-half, half + 1):
                y = cy + j
                if 0 <= cx < MATRIX_SIZE and 0 <= y < MATRIX_SIZE:
                    painter.fillRect(cx * PIXEL_SIZE, y * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, color)

    def mousePressEvent(self, event: QMouseEvent):
        x = event.x() // PIXEL_SIZE
        y = event.y() // PIXEL_SIZE
        if 0 <= x < MATRIX_SIZE and 0 <= y < MATRIX_SIZE:
            if self.current_figure != 'Nessuna':
                self.draw_shape(x, y)
            else:
                current = self.pixels[y][x]
                if current == self.current_color:
                    self.pixels[y][x] = QColor(0, 0, 0)
                else:
                    self.pixels[y][x] = self.current_color
            self.update()

    def draw_shape(self, cx, cy):
        r = self.figure_dim // 2
        if self.current_figure == 'Cerchio':
            for j in range(max(cy - r, 0), min(cy + r + 1, MATRIX_SIZE)):
                dx = int((r ** 2 - (j - cy) ** 2) ** 0.5)
                for i in range(max(cx - dx, 0), min(cx + dx + 1, MATRIX_SIZE)):
                    self.pixels[j][i] = self.current_color
        elif self.current_figure == 'Quadrato':
            for i in range(cx - r, cx + r + 1):
                for j in range(cy - r, cy + r + 1):
                    if 0 <= i < MATRIX_SIZE and 0 <= j < MATRIX_SIZE:
                        self.pixels[j][i] = self.current_color
        elif self.current_figure == 'Triangolo':
            # Triangolo equilatero con la punta in su, centrato su (cx, cy)
            h = self.figure_dim
            for row in range(h):
                y = cy - h // 2 + row
                if 0 <= y < MATRIX_SIZE:
                    # Calcola la larghezza della riga corrente
                    half_base = row * (h // 2) // max(h - 1, 1)
                    for x in range(cx - half_base, cx + half_base + 1):
                        if 0 <= x < MATRIX_SIZE:
                            self.pixels[y][x] = self.current_color
        elif self.current_figure == 'Croce':
            # Croce a forma di più: due linee ortogonali centrate su (cx, cy)
            size = self.figure_dim
            half = size // 2
            # Linea orizzontale
            for i in range(-half, half + 1):
                x = cx + i
                if 0 <= x < MATRIX_SIZE and 0 <= cy < MATRIX_SIZE:
                    self.pixels[cy][x] = self.current_color
            # Linea verticale
            for j in range(-half, half + 1):
                y = cy + j
                if 0 <= cx < MATRIX_SIZE and 0 <= y < MATRIX_SIZE:
                    self.pixels[y][cx] = self.current_color

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Matrix Drawing Interface")
        self.matrices = []
        self.images_json = []  # Lista delle immagini da esportare
        self.layout = QHBoxLayout()  # Cambia in HBoxLayout per layout orizzontale
        self.setLayout(self.layout)

        # Widget per visualizzare il JSON a sinistra
        self.json_view = QTextEdit()
        self.json_view.setReadOnly(True)
        self.json_view.setFixedWidth(350)  # Larghezza fissa solo per il widget JSON
        self.json_view.setMinimumHeight(400)
        self.json_view.setMaximumHeight(800)
        self.layout.addWidget(self.json_view)

        # Colonna centrale con i controlli e le matrici
        self.central_widget = QWidget()
        self.central_layout = QVBoxLayout()
        self.central_widget.setLayout(self.central_layout)
        self.layout.addWidget(self.central_widget)

        # Matrix number selectors
        config_layout = QHBoxLayout()
        self.slave1_spin = QSpinBox()
        self.slave2_spin = QSpinBox()
        self.slave1_spin.setRange(0, 3)
        self.slave2_spin.setRange(0, 3)
        config_layout.addWidget(QLabel("Matrici SLAVE1:"))
        config_layout.addWidget(self.slave1_spin)
        config_layout.addWidget(QLabel("Matrici SLAVE2:"))
        config_layout.addWidget(self.slave2_spin)

        self.apply_button = QPushButton("Applica")
        self.apply_button.clicked.connect(self.generate_matrices)
        config_layout.addWidget(self.apply_button)

        # Pulsante Conferma per aggiungere la configurazione corrente
        self.confirm_button = QPushButton("Conferma")
        self.confirm_button.clicked.connect(self.confirm_current_config)
        config_layout.addWidget(self.confirm_button)

        # Aggiungi il pulsante Salva
        self.save_button = QPushButton("Salva")
        self.save_button.clicked.connect(self.save_matrices)
        config_layout.addWidget(self.save_button)

        # Aggiungi il pulsante Reset
        self.reset_button = QPushButton("Reset")
        self.reset_button.clicked.connect(self.reset_matrices)
        config_layout.addWidget(self.reset_button)

        self.central_layout.addLayout(config_layout)

        # Selettore figura
        figure_layout = QHBoxLayout()
        self.figure_combo = QComboBox()
        self.figure_combo.addItems(FORME)
        figure_layout.addWidget(QLabel("Figura:"))
        figure_layout.addWidget(self.figure_combo)

        # Dimensione figura
        self.size_spin = QSpinBox()
        self.size_spin.setRange(3, 32)
        self.size_spin.setValue(3)
        self.size_spin.valueChanged.connect(self.set_figure_dim)
        figure_layout.addWidget(QLabel("Dimensione:"))
        figure_layout.addWidget(self.size_spin)

        self.figure_combo.currentTextChanged.connect(self.set_figure)
        self.size_spin.valueChanged.connect(self.set_figure_dim)
        self.central_layout.addLayout(figure_layout)

        # Color selector
        colore_layout = QHBoxLayout()
        self.colore_combo = QComboBox()
        self.colore_combo.addItems(COLORI_BASE.keys())
        self.colore_combo.currentTextChanged.connect(self.choose_color)
        colore_layout.addWidget(QLabel("Colore:"))
        colore_layout.addWidget(self.colore_combo)
        self.central_layout.addLayout(colore_layout)

        # Scroll area for matrices
        self.scroll_area = QScrollArea()
        self.scroll_area.setWidgetResizable(True)
        self.matrices_container = QWidget()
        self.matrices_layout = QHBoxLayout()
        self.matrices_container.setLayout(self.matrices_layout)
        self.scroll_area.setWidget(self.matrices_container)
        self.central_layout.addWidget(self.scroll_area)

        # Imposta solo la dimensione minima della finestra per mostrare almeno una matrice
        min_matrices = 1
        width = min_matrices * MATRIX_SIZE * PIXEL_SIZE + 100  # +100 per margini e scroll
        height = MATRIX_SIZE * PIXEL_SIZE + 180  # +180 per controlli sopra
        self.setMinimumWidth(width)
        self.setMinimumHeight(height)
        # Rimuovi i settaggi di larghezza massima

        self.matrices = []

    def confirm_current_config(self):
        # Raggruppa le matrici per slave
        slave1_matrices = []
        slave2_matrices = []
        for matrix in self.matrices:
            if matrix.name.startswith("SLAVE1"):
                slave1_matrices.append(matrix)
            elif matrix.name.startswith("SLAVE2"):
                slave2_matrices.append(matrix)

        # Ordina le matrici per indice numerico crescente (_1, _2, ...)
        def matrix_index(m):
            return int(m.name.split('_')[1])
        slave1_matrices.sort(key=matrix_index)
        slave2_matrices.sort(key=matrix_index)

        images_json = []
        for slave_name, matrices in [
            ("SLAVE1", slave1_matrices),
            ("SLAVE2", slave2_matrices)
        ]:
            if not matrices:
                continue
            n_matrices = len(matrices)
            pixels = []
            # ATTENZIONE: y è la coordinata orizzontale (colonna), x la verticale (riga)
            # La matrice più a sinistra (indice 0) ha y_offset=0, la successiva a destra +MATRIX_SIZE, ecc.
            # Ordina le matrici in ordine decrescente di indice: la più a sinistra (indice più alto) per prima
            matrices_sorted = sorted(matrices, key=lambda m: int(m.name.split('_')[1]), reverse=True)
            pixels = []
            for pos, matrix in enumerate(matrices_sorted):
                x_offset = pos * MATRIX_SIZE  # x = orizzontale (colonna)
                for y in range(MATRIX_SIZE):  # y = verticale (riga)
                    for x in range(MATRIX_SIZE):  # x = orizzontale (colonna)
                        color = matrix.pixels[y][x]
                        r, g, b, _ = color.getRgb()
                        if (r, g, b) != (0, 0, 0):
                            x_global = x + x_offset  # orizzontale
                            y_global = y  # verticale
                            pixels.append([x_global, y_global, r, g, b])
            if pixels:
                images_json.append({
                    "CONTROLLER_TARGET": slave_name,
                    "PIXELS": pixels
                })
        # AGGIUNGI (non sovrascrivere) il nuovo stimolo
        self.images_json.extend(images_json)
        self.json_view.setPlainText(json.dumps(self.images_json, indent=2))

    def generate_matrices(self):
        # Clear current layout
        for i in reversed(range(self.matrices_layout.count())):
            child = self.matrices_layout.itemAt(i).widget()
            if child:
                child.setParent(None)
        self.matrices.clear()

        # SLAVE1: centrale -> sinistra
        n1 = self.slave1_spin.value()
        slave1_names = []
        if n1 > 0:
            center = n1 // 2
            for i in range(n1):
                pos = center - i if i % 2 == 1 else center + (i // 2)
                slave1_names.append((pos, f"SLAVE1_{i+1}"))
            # Ordina per posizione crescente (sinistra -> destra)
            slave1_names.sort()
            for _, name in slave1_names:
                self.add_matrix(name)

        # SLAVE2: destra -> centro
        n2 = self.slave2_spin.value()
        slave2_names = []
        if n2 > 0:
            # Indici da n2 a 1 (decrescente)
            for i in range(n2, 0, -1):
                pos = n2 - i  # posizione da destra verso sinistra
                slave2_names.append((pos, f"SLAVE2_{i}"))
            # Ordina per posizione crescente (da destra verso sinistra)
            slave2_names.sort()
            for _, name in slave2_names:
                self.add_matrix(name)

        # Aggiorna la visualizzazione per mostrare la griglia
        for matrix in self.matrices:
            matrix.update()

        # Ridimensiona la finestra in base al numero di matrici
        num_matrices = len(self.matrices)
        if num_matrices > 0:
            width = num_matrices * MATRIX_SIZE * PIXEL_SIZE + 100  # +100 per margini e scroll
            height = MATRIX_SIZE * PIXEL_SIZE + 180  # +180 per controlli sopra
            self.setMinimumWidth(width)
            self.setMinimumHeight(height)
            # Rimuovi i settaggi di larghezza massima
            self.adjustSize()  # Adatta la finestra allo spazio occupato

    def add_matrix(self, name):
        container = QVBoxLayout()
        label = QLabel(name)
        label.setAlignment(Qt.AlignCenter)
        matrix = MatrixWidget(name)
        # Aggiorna subito colore, figura e dimensione secondo i menu attuali
        matrix.set_color(COLORI_BASE[self.colore_combo.currentText()])
        matrix.set_figure(self.figure_combo.currentText())
        matrix.set_figure_dim(self.size_spin.value())
        container_widget = QWidget()
        container.addWidget(label)
        container.addWidget(matrix)
        container_widget.setLayout(container)
        self.matrices_layout.addWidget(container_widget)
        self.matrices.append(matrix)

    def save_matrices(self):
        # Salva il JSON attualmente visualizzato
        options = QFileDialog.Options()
        filename, _ = QFileDialog.getSaveFileName(self, "Salva Matrici", "", "JSON Files (*.json)", options=options)
        if filename:
            with open(filename, "w") as f:
                import json
                json.dump(self.images_json, f, indent=2)

    def reset_matrices(self):
        for matrix in self.matrices:
            for y in range(MATRIX_SIZE):
                for x in range(MATRIX_SIZE):
                    matrix.pixels[y][x] = QColor(0, 0, 0)
            matrix.update()
        self.images_json = []
        self.json_view.setPlainText("")

    def choose_color(self, color):
        for m in self.matrices:
            m.set_color(COLORI_BASE[color])

    def set_figure(self, figure):
        for m in self.matrices:
            m.set_figure(figure)

    def set_figure_dim(self, dim):
        for m in self.matrices:
            m.set_figure_dim(dim)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())
