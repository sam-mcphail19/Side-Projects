package engine.graphics;

public class StaticShader extends ShaderProgram{

    private static final String VERTEX_FILE = "res/shaders/vertexShader.vsh";
    private static final String FRAGMENT_FILE = "res/shaders/fragmentShader.fsh";

    public StaticShader() {
        super(VERTEX_FILE, FRAGMENT_FILE);
    }

    @Override
    protected void bindAttributes() {
        super.bindAttribute(0, "position");
        super.bindAttribute(1, "color");
        super.bindAttribute(2, "textureCoord");
    }
}
