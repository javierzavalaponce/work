# grafica.gp
set terminal png size 800,600
set output "solucion.png"
set xlabel "Tiempo (t)"
set ylabel "Solución"
set grid
set title "Solución de la Ecuación Diferencial"
plot "solucion.dat" using 1:2 with lines linewidth 2 title "x(t)"

