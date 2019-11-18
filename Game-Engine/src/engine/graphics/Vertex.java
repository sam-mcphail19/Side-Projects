package engine.graphics;

import engine.math.Vector3f;

public class Vertex {
    private Vector3f position;

    public Vertex(float x, float y, float z){
        position = new Vector3f(x, y, z);
    }

    public Vector3f getPosition() {
        return position;
    }

    public void setPosition(float x, float y, float z){
        position.setX(x);
        position.setY(y);
        position.setZ(z);
    }
}
