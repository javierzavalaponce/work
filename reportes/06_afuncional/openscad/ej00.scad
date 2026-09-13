// ============================================
//  NORMA vs DISTANCIA
// 
// ============================================

// ===== PARÁMETROS =====
origen = [4, 0, 0];   //  para mover el origen
punto1 = [3, 4, 2];
punto2 = [1, 6, 5];

// ===== MÓDULO PARA DIBUJAR LÍNEAS (VERSIÓN HULL) =====
module linea(p1, p2, r=0.05) {
    
    // "puente" entre dos esferas usando hull()
    hull() {
        translate(p1) sphere(r);
        translate(p2) sphere(r);
    }
}


// 1. El origen ( en rojo)
color("red") 
translate(origen) 
sphere(r=0.3);

// 2. Los dos puntos (azules)
color("blue") 
translate(punto1) 
sphere(r=0.4);

color("blue") 
translate(punto2) 
sphere(r=0.4);

// 3. Línea que representa la NORMA de punto1 (del ORIGEN a punto1)
color("green", 0.7) 
linea(origen, punto1, 0.08);

// 4. Línea que representa la NORMA de punto2 (del ORIGEN a punto2)
color("green", 0.7) 
linea(origen, punto2, 0.08);

// 5. Línea que representa la DISTANCIA (entre punto1 y punto2)
color("magenta", 0.9) 
linea(punto1, punto2, 0.1);

// ===== CÁLCULOS Y ETIQUETAS =====
norma1 = norm(punto1);
norma2 = norm(punto2);
distancia = norm(punto1 - punto2);

// Mostrar en consola
echo("Norma de punto1 (distancia al origen):", norma1);
echo("Norma de punto2 (distancia al origen):", norma2);
echo("Distancia entre punto1 y punto2:", distancia);

