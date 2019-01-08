PShape euroFighter;
float x;
float y;
float z;

void setup() {
  size(640, 360, P3D);
  euroFighter = loadShape("Eurofighter.obj");
}

void draw() {
  background(0);
  lights();
  translate(mouseX,mouseY, -80);
  rotateX(2.7);
  rotateY(y);
  rotateZ(z);
  //box(60);
  scale(15);
  shape(euroFighter);
  x++;
  delay(100);
}
