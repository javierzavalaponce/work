
d = 450;
radio=25;

module pendulo(theta=0)
{
    rotate([theta,0,0])
        translate([0,0,-d]) {
            cylinder(h=d, r=3);
            sphere(radio);
        }
}

theta_max = 30;
theta = theta_max * sin(360*$t) * exp(-2*$t);
pendulo(theta);

