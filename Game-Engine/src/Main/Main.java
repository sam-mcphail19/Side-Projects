package Main;

import engine.graphics.Mesh;
import engine.graphics.Renderer;
import engine.graphics.Vertex;
import engine.io.Window;

public class Main implements Runnable{

    public Thread game;
    private Window window;
    private final int WIDTH = 1280, HEIGHT=760;
    private final String TITLE = "Game";
    private Renderer renderer;

    private Vertex[] vertices = new Vertex[] {
            new Vertex(-0.5f,  0.0f, 0.0f),
            new Vertex(-0.5f, -0.5f, 0.0f),
            new Vertex(0.0f, -0.5f, 0.0f),
            new Vertex(0.5f, 0.0f, 0.0f),
            new Vertex(0.5f, 0.5f, 0.0f),
            new Vertex(0.0f, 0.5f, 0.0f),
    };

    private Mesh mesh = new Mesh(vertices, new int[] {0, 1, 2, 3, 4, 5});

    public void start(){
        game = new Thread(this, "game");
        game.start();
    }

    private void init() {
        window = new Window(WIDTH, HEIGHT, TITLE);
        window.setBackgroundColor(1.0f,1.0f,0.0f);
        renderer = new Renderer();
        mesh.create();
    }

    public void run() {
        init();

        while (!window.shouldClose()) {
            update();
            render();
        }
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