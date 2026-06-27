arm_length=250; //mm
pendulo_length=230;
pared=2;
diam_tubo=19;

module arm(){
  rotate([90,0,0])
  difference(){
    cylinder(h=arm_length,r=diam_tubo/2.0,center=false);
    cylinder(h=arm_length+1,r=(diam_tubo/2.0)-pared,center=false);
  } 
}

module pendulo(){
union(){
    cylinder(h=pendulo_length,r=5,center=false);
    cylinder(h=50,r=15,center=false);
}
}

module furuta(theta_a=0,theta_p=0){
  rotate([0,0,theta_a]){
    color("orangered")
    arm();
    color("gray")
    rotate([0,-theta_p,0])
    translate([0,-arm_length,-pendulo_length])
    pendulo();
  }
}

furuta(10,10);











