package engine.objects;

import engine.graphics.Mesh;
import engine.math.Vector3f;

import static engine.math.Vector3f.*;

public class Entity {

    private Mesh mesh;
    private Vector3f position, direction, scale;
    private float speed;

    public Entity(Mesh mesh, Vector3f position, Vector3f direction, Vector3f scale, float speed) {
        this.mesh = mesh;
        this.position = position;
        this.direction = direction;
        this.scale = scale;
        this.speed = speed;
    }

    public void update(){
        // normalize direction vector if it is not
        position = add(position, direction.scale(speed));
    }

    public Mesh getMesh() {
        return mesh;
    }

    public void setMesh(Mesh mesh) {
        this.mesh = mesh;
    }

    public Vector3f getPosition() {
        return position;
    }

    public void setPosition(Vector3f position) {
        this.position = position;
    }

    public Vector3f getDirection() {
        return direction;
    }

    public void setDirection(Vector3f direction) {
        this.direction = direction;
    }

    public Vector3f getScale() {
        return scale;
    }

    public void setScale(Vector3f scale) {
        this.scale = scale;
    }

    public float getSpeed() {
        return speed;
    }

    public void setSpeed(float speed) {
        this.speed = speed;
    }
}
