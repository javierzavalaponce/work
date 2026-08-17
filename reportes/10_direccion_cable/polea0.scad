diametro_interior = 25.4;
diametro_exterior = 3 * 25.4;
diametro_cabeza_chicote = 5;
altura=35;
profundidad_ranura_long = 6;
profundidad_ranura_chic = 2;

radio_interior = diametro_interior / 2;
radio_exterior = diametro_exterior / 2;
radio_chicote  = diametro_cabeza_chicote / 2;


module arandela_ranura() {
    difference() {
        cylinder(h=2+0.1,   r=radio_exterior+0.01, center=true);
        cylinder(h=2, r=radio_exterior-profundidad_ranura_chic,center=true);
    }
}

module barra_hueca() {
    difference() {
        cylinder(h=altura,   r=radio_exterior, center=true);
        cylinder(h=altura+1, r=radio_interior, center=true);
    }
}


module polea_manubrio(){
    difference() {
        barra_hueca();
    
        /* Dos orificios para chicotes*/
        /*1:*/
        translate([0,30,0])
            cylinder(h=altura+2, r=radio_chicote, center=true);
        /*2:*/
        translate([0,-30,0])
            cylinder(h=altura+2, r=radio_chicote, center=true);        
    
    
        /* Dos ranuras longitudinales*/
        /*1:*/
        translate([0,+radio_exterior-profundidad_ranura_long/2,0])
            cube([2,profundidad_ranura_long,altura+1],center=true);        
        /*2:*/
        translate([0,-radio_exterior+profundidad_ranura_long/2,0])
            cube([2,profundidad_ranura_long,altura+1],center=true);        
    
    
        translate([0,0,10])
        arandela_ranura();
    
    
        translate([0,0,- 10])
        arandela_ranura();
    } 
}


module manubrio(){
    rotate([90,0,0])
       cylinder(h=420, r=10, center=true);
}


angulo = 90*sin(360*$t);
rotate([0,0,angulo]){
   polea_manubrio();

translate([0,0,100])
*manubrio();

}




