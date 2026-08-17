$fa = 1;
$fs = 0.5;

total_len=39;
diam_total = 25.4*2;
diam_ex1 = 33.4;
diam_ex3 = 33.4;

diametro_interior = 28.6;
diametro_cabeza_chicote = 6.35;
profundidad_ranura_chic = 2;


l1=5;
l2=25.4*2; //ref only
l3=18;
l3_1=3; // bode polea

ranura_prof  = 3;
ranura_ancho = 2;

radio_interior = diametro_interior / 2;
radio_total = diam_total / 2;
radio_ex1 = diam_ex1 / 2;
radio_ex3 = diam_ex3 / 2;
radio_ex5 = (diam_total / 2)-ranura_prof;


module barra_hueca() {
    difference() {
        cylinder(h=total_len,   r=radio_total, center=true);
        cylinder(h=total_len+0.1, r=radio_interior, center=true);
    }
}

module barra_hueca_cilindrada1() {
    translate([0,0,+0.1+(total_len/2)-(l1/2)])
    difference() {
        cylinder(h=l1,   r=radio_total+0.1, center=true);
        cylinder(h=l1+0.1, r=radio_ex1, center=true);
    }
}


module barra_hueca_cilindrada3() {
    translate([0,0,-0.1-(total_len/2)+(l3/2)])
    difference() {
        cylinder(h=l3,   r=radio_total+0.1, center=true);
        cylinder(h=l3+0.1, r=radio_ex3, center=true);
    }
}

module ranura1() {
    translate([0,0,(total_len/2)-l1-l3_1-(ranura_ancho/2)])
    difference() {
        cylinder(h=ranura_ancho,   r=radio_total+0.1, center=true);
        cylinder(h=ranura_ancho+0.1, r=radio_ex5, center=true);
    }
}


module ranura3() {
    translate([0,0,(total_len/2)-l1-l3_1-(ranura_ancho*4.5)])
    difference() {
        cylinder(h=ranura_ancho,   r=radio_total+0.1, center=true);
        cylinder(h=ranura_ancho+0.1, r=radio_ex5, center=true);
    }
}

module perfo_un_cuarto_de_pulgada() {
    translate([0,0,-(total_len/2)+9])    
    rotate([0,90,0])
    cylinder(h = 35, r = 6.35/2, center = true); //diam de 1/4 de pulgada.
}


module perfo_chicote1() {
    translate([radio_total-(6.35/2)-1,0,0])    
    cylinder(h = 32, r = 6.35/2, center = true); //diam de 1/4 de pulgada.
}


module perfo_chicote2() {
    translate([-radio_total+(6.35/2)+1,0,0])    
    cylinder(h = 32, r = 6.35/2, center = true); //diam de 1/4 de pulgada.
}


module ranura_vertical_chicote1() {
    translate([radio_total,0,0])    
    cube([5,ranura_ancho,32],true);
}

module ranura_vertical_chicote2() {
    translate([-radio_total,0,0])    
    cube([5,ranura_ancho,32],true);
}

module all() {
    difference(){
       barra_hueca();
       barra_hueca_cilindrada1();
       barra_hueca_cilindrada3();
       ranura1();
       ranura3();
       perfo_un_cuarto_de_pulgada();
       perfo_chicote1();
       perfo_chicote2();
       ranura_vertical_chicote1();
       ranura_vertical_chicote2();
    }
}

angulo = 90*sin(360*$t);
rotate([0,0,angulo])
all();





