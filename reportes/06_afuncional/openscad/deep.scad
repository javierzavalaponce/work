// ============================================================
//  Convergencia en un espacio de funciones (Banach / Hilbert)
//  θₙ(t) = A · Σ_{k=0}^{n} (-1)^k (ω t)^{2k} / (2k)!  →  A·cos(ω t)
// ============================================================

$fn = 16;

// --- Parámetros ---
A     = 5;      // amplitud (grados, conceptual)
omega = 1;      // frecuencia angular
T     = 3.5;    // intervalo de tiempo [0, T]
N     = 6;      // índice máximo de aproximación (n = 0..N)
steps = 120;    // muestras por curva

sx = 6;         // escala en t
sy = 2;         // escala en θ
sz = 6;         // separación entre planos n

// --- Utilidades matemáticas ---
function fact(n) = n <= 1 ? 1 : n * fact(n - 1);

function taylor_cos(x, n, k = 0) =
    k > n ? 0 :
        ((k % 2 == 0) ? 1 : -1) * pow(x, 2*k) / fact(2*k)
        + taylor_cos(x, n, k + 1);

function theta_n(t, n)  = A * taylor_cos(omega * t, n);
function theta_exact(t) = A * cos(omega * t);

// --- Geometría ---
module capsule(p, q, r) {
    hull() { translate(p) sphere(r); translate(q) sphere(r); }
}
module polyline(pts, r) {
    for (i = [0 : len(pts) - 2]) capsule(pts[i], pts[i+1], r);
}

function curve_pts(n) =
    [for (i = [0 : steps])
        let (t = T * i / steps)
        [t * sx, theta_n(t, n) * sy, n * sz]
    ];

function exact_pts() =
    [for (i = [0 : steps])
        let (t = T * i / steps)
        [t * sx, theta_exact(t) * sy, (N + 1) * sz]
    ];

// --- Ejes ---
color("silver") {
    capsule([0, 0, 0], [T * sx + 2, 0, 0], 0.08);              // t
    capsule([0, -60, 0], [0, 20, 0], 0.08);                     // θ
    capsule([0, 0, 0], [0, 0, (N + 2) * sz], 0.08);             // n
}

// --- Curvas aproximantes θₙ ---
for (n = [0 : N]) {
    color([1 - 0.12*n, 0.25 + 0.05*n, 0.85 - 0.10*n, 0.9])
        polyline(curve_pts(n), 0.18);
}

// --- Curva exacta (límite) ---
color("black") polyline(exact_pts(), 0.28);

// --- Bob final del péndulo en cada nivel ---
for (n = [0 : N]) {
    p = [T * sx, theta_n(T, n) * sy, n * sz];
    color("orange") translate(p) sphere(0.55);
}
color("red") translate([T * sx, theta_exact(T) * sy, (N+1) * sz])
    sphere(0.7);

// --- Barras de error: ‖θₙ - θ_exact‖∞ (aprox.) ---
for (n = [0 : N]) {
    y_n  = theta_n(T, n) * sy;
    y_ex = theta_exact(T) * sy;
    color([1, 0.2, 0.1, 0.75])
        capsule([T * sx, y_n, n * sz],
                [T * sx, y_ex, n * sz], 0.07);
}


