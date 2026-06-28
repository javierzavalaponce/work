// ==================== PARÁMETROS ====================
L_pendulo = 225;          
L_peso = 30;              
r_peso = 15;
r_varilla = 5;

armlength = 237;
pared = 2;
diam_tubo_arm = 19;
radio_ext = diam_tubo_arm / 2;
radio_int = radio_ext - pared;

// ==================== MÓDULOS ====================


// Brazo: se extiende a lo largo del eje Y positivo
module arm(){
    rotate([90, 0, 0]) {
        difference(){
            cylinder(h=armlength, r=radio_ext, center=false);
            cylinder(h=armlength + 2, r=radio_int, center=false);
        }
    }
}



// Péndulo: su PIVOTE está en el origen (parte superior de la varilla)
module pendulo(angulo){
    rotate([0, -angulo, 0]) { // Gira alrededor del eje Y (eje del brazo)
        // Varilla (baja desde 0 hasta -225)
        translate([0, 0, -L_pendulo])
            cylinder(h=L_pendulo, r=r_varilla, center=false);
        // Peso (situado a 15mm del extremo)
        translate([0, 0, -210])
            cylinder(h=L_peso, r=r_peso, center=false);
    }
}



// Sistema completo del péndulo de Furuta
module furuta(theta, alpha){
    rotate([0, 0, theta]) {        // 1. Rotación del brazo en el plano horizontal
        color("orangered")
        arm();                      // Dibuja el brazo desde el origen
        
        color("gray")
        translate([0,-armlength, 0]) { // 2. Traslada al extremo del brazo
            pendulo(alpha);          // 3. Dibuja el péndulo con su inclinación
        }
    }
}

// ==================== EJEMPLO ====================
// theta = ángulo del brazo (en grados), alpha = inclinación del péndulo (en grados)
//furuta(360*$t, 30*sin(360*$t*2)); 
furuta(10,40);
