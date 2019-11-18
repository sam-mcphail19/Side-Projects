package Main;

import engine.graphics.*;
import engine.io.Window;

public class Main implements Runnable{

    public Thread game;
    private Window window;
    private final int WIDTH = 1280, HEIGHT=760;
    private final String TITLE = "Game";
    private Renderer renderer;
    private ShaderProgram shader;

    private Vertex[] vertices = new Vertex[] {
            new Vertex(0.5f,  0.5f, 0.0f),
            new Vertex(0.5f, -0.5f, 0.0f),
            new Vertex(-0.5f, -0.5f, 0.0f),
            new Vertex(-0.5f,0.5f, 0.0f)
    };

    private Mesh mesh = new Mesh(vertices, new int[] {0, 1, 2, 3, 0, 2});

    public void start(){
        game = new Thread(this, "game");
        game.start();
    }

    private void init() {
        window = new Window(WIDTH, HEIGHT, TITLE);
        window.setBackgroundColor(0.4f,0.4f,0.8f);
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
        shader.cleanUp();
        window.destroy();
    }

    private void update(){
        window.update();
    }

    private void render(){
        renderer.renderMesh(mesh);
        window.swapBuffers();
    }

    public static void main(String[] args) {
        new Main().start();
    }

}