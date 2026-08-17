total_len=45;
diam_ex1 = 85;
diam_ex2 = 32;
diametro_interior = 25.4;
diametro_cabeza_chicote = 5;
profundidad_ranura_chic = 2;



radio_interior = diametro_interior / 2;
radio_ex1 = diam_ex1 / 2;
radio_ex2 = diam_ex2 / 2;

module barra_hueca() {
    difference() {
        cylinder(h=total_len,   r=diam_ex1, center=true);
        cylinder(h=total_len+1, r=diametro_interior, center=true);
    }
}

barra_hueca();

