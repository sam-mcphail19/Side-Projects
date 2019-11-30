package engine.math;

public class Vector3f {

    private float x,y,z;

    public Vector3f(float x, float y, float z){
        this.x = x;
        this.y = y;
        this.z = z;
    }

    public Vector3f scale(float magnitude){
        return new Vector3f(x*magnitude, y*magnitude, z*magnitude);
    }

    public static Vector3f add(Vector3f vec1, Vector3f vec2) {
        return new Vector3f(
                vec1.getX() + vec2.getX(),
                vec1.getY() + vec2.getY(),
                vec1.getZ() + vec2.getZ());
    }

    public float getX() {
        return x;
    }

    public void setX(float x) {
        this.x = x;
    }

    public float getY() {
        return y;
    }

    public void setY(float y) {
        this.y = y;
    }

    public float getZ() {
        return z;
    }

    public void setZ(float z) {
        this.z = z;
    }

}
