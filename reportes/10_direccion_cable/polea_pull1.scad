total_len=45;
diam_ex1 = 85;
diam_ex2 = 32;
diametro_interior = 25.4;
diametro_cabeza_chicote = 5;
profundidad_ranura_chic = 2;
l1=20;

radio_interior = diametro_interior / 2;
radio_ex1 = diam_ex1 / 2;
radio_ex2 = diam_ex2 / 2;

module barra_hueca() {
    difference() {
        cylinder(h=total_len,   r=radio_ex1, center=true);
        cylinder(h=total_len+0.1, r=radio_interior, center=true);
    }
}

module barra_hueca_cilindrada1() {
    translate([0,0,-0.1-(total_len/2)+(l1/2)])
    difference() {
        cylinder(h=l1,   r=radio_ex1+0.1, center=true);
        cylinder(h=l1+0.1, r=radio_ex2, center=true);
    }
}


module all() {
    difference(){
       barra_hueca();
       barra_hueca_cilindrada1();
    }
}

all();


