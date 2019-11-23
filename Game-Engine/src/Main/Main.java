package Main;

import engine.graphics.*;
import engine.io.Window;
import engine.math.Vector2f;
import engine.math.Vector3f;
import engine.math.Vector4f;

public class Main implements Runnable{

    public Thread game;
    private Window window;
    private final int WIDTH = 1280, HEIGHT=760;
    private final String TITLE = "Game";
    private Renderer renderer;
    private StaticShader shader;

    private Vertex[] vertices = new Vertex[] {
            new Vertex(
                    new Vector3f(-0.5f,  0.7f,0.0f),
                    new Vector4f(1.0f, 1.0f, 1.0f, 0.5f),
                    new Vector2f(0.0f, 0.0f)),
            new Vertex(
                    new Vector3f(-0.5f, -0.7f, 0.0f),
                    new Vector4f(1.0f, 1.0f, 1.0f, 0.5f),
                    new Vector2f(0.0f, 1.0f)),
            new Vertex(
                    new Vector3f( 0.5f, -0.7f, 0.0f),
                    new Vector4f(0.0f, 1.0f, 1.0f, 0.5f),
                    new Vector2f(1.0f, 1.0f)),
            new Vertex(
                    new Vector3f( 0.5f,  0.7f, 0.0f),
                    new Vector4f(1.0f, 1.0f, 1.0f, 0.5f),
                    new Vector2f(1.0f, 0.0f))
    };
    private int[] indices = new int[] {0, 1, 2, 2, 3, 0};

    private Image image = Image.create("res/img/thanos.png");
    private Mesh mesh = new Mesh(vertices, indices, image);
    //private Mesh mesh = new Mesh(vertices, indices, null);

    private void start(){
        game = new Thread(this, "game");
        game.start();
    }

    private void init() {
        window = new Window(WIDTH, HEIGHT, TITLE);
        window.setBackgroundColor(0.1f,0.1f,0.1f, 1.0f);
        renderer = new Renderer();
        shader = new StaticShader();
        mesh.create();
    }

    public void run() {
        init();
        while (!window.shouldClose()) {
            update();
            shader.start();
            render();
            shader.stop();
        }
        close();
    }

    private void update(){
        window.update();
    }

    private void render(){
        //renderer.renderMeshWireFrame(mesh);
        renderer.renderMeshFill(mesh);
        window.swapBuffers();
    }

    private void close(){
        mesh.destroy();
        shader.cleanUp();
        window.destroy();
    }

    public static void main(String[] args) {
        new Main().start();
    }

}