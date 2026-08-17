$fa = 1;
$fs = 0.5;

total_len=44;
diam_total = 25.4*2;

diam_ex1 = 27.4;
diam_ex2 = 32;
diam_ex4 = 32;

diametro_interior = 25.4;
diametro_cabeza_chicote = 5;
profundidad_ranura_chic = 2;


l1=5;
l2=5;
l3=20; //ref only
l3_1=3; // bode polea
l4=18;

ranura_prof  = 3;
ranura_ancho = 2;

radio_interior = diametro_interior / 2;
radio_total = diam_total / 2;
radio_ex1 = diam_ex1 / 2;
radio_ex2 = diam_ex2 / 2;
radio_ex4 = diam_ex4 / 2;
radio_ex5 = (diam_total / 2)-ranura_prof;


caja_x=3.5;
caja_y=10;

m5_prof = 10;

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

module barra_hueca_cilindrada2() {
    translate([0,0,0.11+(total_len/2)-(l1)-(l1/2)])
    difference() {
        cylinder(h=l2,   r=radio_total+0.1, center=true);
        cylinder(h=l2+0.1, r=radio_ex2, center=true);
    }
}


module barra_hueca_cilindrada4() {
    translate([0,0,-0.1-(total_len/2)+(l4/2)])
    difference() {
        cylinder(h=l4,   r=radio_total+0.1, center=true);
        cylinder(h=l4+0.1, r=radio_ex4, center=true);
    }
}



module ranura1() {
    translate([0,0,(total_len/2)-l1-l2-l3_1-(ranura_ancho*0)-(ranura_ancho/2)])
    difference() {
        cylinder(h=ranura_ancho,   r=radio_total+0.1, center=true);
        cylinder(h=ranura_ancho+0.1, r=radio_ex5, center=true);
    }
}



module ranura3() {
    translate([0,0,(total_len/2)-l1-l2-l3_1-(ranura_ancho*4)-(ranura_ancho/2)])
    difference() {
        cylinder(h=ranura_ancho,   r=radio_total+0.1, center=true);
        cylinder(h=ranura_ancho+0.1, r=radio_ex5, center=true);
    }
}



module fresado1() {
    translate([(diam_total/2)-(caja_x/2),0,0])
    cube([caja_x,caja_y,l3+10],true);
}

module fresado2() {
    translate([-(diam_total/2)+(caja_x/2),0,0])
    cube([caja_x,caja_y,l3+10],true);
}


module cuerda_internaM5_1() {
    translate([(diam_total/2)-(m5_prof/2)-caja_x+0.1 ,0,
              (total_len/2)-l1-l2-l3_1-1.5*ranura_ancho])    
    rotate([0,90,0])
    cylinder(h = m5_prof, r = 2.15, center = true); //diam 4.3 para roscar M5
}


module cuerda_internaM5_2() {
    translate([-(diam_total/2)+(m5_prof/2)+caja_x-0.1 ,0,
              (total_len/2)-l1-l2-l3_1-3.5*ranura_ancho])    
    rotate([0,90,0])
    cylinder(h = m5_prof, r = 2.15, center = true); //diam 4.3 para roscar M5
}


module perfo_un_cuarto_de_pulgada() {
    translate([0,0,-(total_len/2)+9])    
    rotate([0,90,0])
    cylinder(h = 35, r = 6.35/2, center = true); //diam de 1/4 de pulgada.
}


echo("dist borde sup a perfo1", l1+l2+l3_1+1.5*ranura_ancho);
echo("dist borde sup a perfo2", l1+l2+l3_1+3.5*ranura_ancho);

module all() {
    difference(){
       barra_hueca();
       barra_hueca_cilindrada1();
       barra_hueca_cilindrada2();
       barra_hueca_cilindrada4();
       ranura1();
       ranura3();
       fresado1();
       fresado2();
       cuerda_internaM5_1();
       cuerda_internaM5_2();
       perfo_un_cuarto_de_pulgada();
    }
}



angulo = 90*sin(360*$t);
rotate([0,0,angulo])
all();





