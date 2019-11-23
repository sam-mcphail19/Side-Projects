package engine.graphics;

import engine.math.Vector2f;
import engine.math.Vector3f;
import engine.math.Vector4f;

public class Vertex {
    private Vector3f position;
    private Vector4f color;
    private Vector2f textureCoord;

    public Vertex(Vector3f position, Vector4f color, Vector2f textureCoord){
        this.position = position;
        this.color = color;
        this.textureCoord = textureCoord;
    }

    public void setPosition(float x, float y, float z){
        position.setX(x);
        position.setY(y);
        position.setZ(z);
    }

    public Vector3f getPosition() {
        return position;
    }

    public Vector4f getColor() {
        return color;
    }

    public Vector2f getTextureCoord() {
        return textureCoord;
    }
}
