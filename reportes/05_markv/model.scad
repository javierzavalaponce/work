// ==========================================
// PÉNDULO DE FURUTA - PARÁMETROS MECÁNICOS
// ==========================================

// --- Parámetros Geométricos (los que usará Python) ---
d = 230;        // Longitud del brazo (mm) -> distancia eje motor a eje péndulo
L = 350;        // Longitud del péndulo (mm) -> distancia eje péndulo a masa
radio_eje = 8;  // Radio del eje del péndulo (mm)

// --- Parámetros de Masas (para calcular inercias) ---
masa_brazo = 150;   // gramos
masa_pendulo = 300; // gramos (incluye la masa del extremo)

// ==========================================
// MODELADO DE PIEZAS (Ejemplo simplificado)
// ==========================================

// 1. Brazo rotatorio (conexión motor - péndulo)
module brazo() {
    color("Silver") {
        rotate([0, 0, 0]) 
        cube([d, 20, 10], center=true); // Brazo rectangular
        // Agujero para el eje del motor
        translate([-d/2, 0, 0]) 
        cylinder(r=5, h=12, center=true, $fn=30);
        // Agujero para el eje del péndulo (en el extremo)
        translate([d/2, 0, 0]) 
        cylinder(r=radio_eje, h=12, center=true, $fn=30);
    }
}

// 2. Péndulo (varilla + masa en extremo)
module pendulo() {
    color("Gold") {
        // Varilla
        rotate([0, 0, 0]) 
        translate([0, 0, -L/2]) 
        cube([6, 6, L], center=true);
        // Masa en el extremo (esfera)
        translate([0, 0, -L]) 
        sphere(r=20, $fn=30);
        // Agujero para el eje en la parte superior
        translate([0, 0, 0]) 
        cylinder(r=radio_eje, h=10, center=true, $fn=30);
    }
}

// ==========================================
// ENSAMBLAJE FINAL
// ==========================================

// El péndulo cuelga del extremo del brazo
rotate([0, 0, 45]) { // Brazo girado 45° para vista
    brazo();
    translate([d, 0, 0]) { // Posicionar péndulo en el extremo
        pendulo();
    }
}

// ==========================================
// EXPORTAR PARÁMETROS PARA PYTHON (Formato JSON)
// ==========================================
// Puedes copiar estos valores manualmente o usar un script 
// para extraerlos del archivo .scad
echo("PARAMETROS_PARA_PYTHON:");
echo(str("d = ", d/1000, "  # metros"));
echo(str("L = ", L/1000, "  # metros"));
echo(str("masa_brazo = ", masa_brazo/1000, "  # kg"));
echo(str("masa_pendulo = ", masa_pendulo/1000, "  # kg"));



