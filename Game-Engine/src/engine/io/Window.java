package engine.io;

import org.lwjgl.glfw.GLFWErrorCallback;
import org.lwjgl.glfw.GLFWVidMode;

import org.lwjgl.opengl.GL;
import org.lwjgl.opengl.GL11;

import static org.lwjgl.glfw.GLFW.*;

import engine.math.Vector4f;

public class Window {
    private long handle;
    private int width;
    private int height;
    private String title;
    private int frames;
    private static long time;
    private Vector4f background = new Vector4f(0,0,0, 1);

    public Window(int width, int height, String title){
        this.width = width;
        this.height = height;
        this.title = title;
        create();
    }

    private void create(){
        GLFWErrorCallback.createPrint(System.err).set();

        if (!glfwInit())
            throw new IllegalStateException("Unable to initialize GLFW");

        handle = glfwCreateWindow(width, height, title, 0, 0);

        if (handle == 0)
            throw new RuntimeException("Failed to create the GLFW window");

        // Get the resolution of the primary monitor
        GLFWVidMode vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        glfwSetWindowPos(handle,
                (vidmode.width() - width) / 2,
                (vidmode.height() - height) / 2); // Center the window
        glfwMakeContextCurrent(handle); // Make the OpenGL context current

        GL.createCapabilities();
        GL11.glEnable(GL11.GL_DEPTH_TEST);

        glfwShowWindow(handle); // Make the window visible
        glfwSwapInterval(1); // Enable v-sync

        time = System.currentTimeMillis();
    }

    public void update(){

        GL11.glClearColor(background.getX(), background.getY(), background.getZ(), background.getW());
        GL11.glClear(GL11.GL_COLOR_BUFFER_BIT | GL11.GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();

        frames++;
        // if more than a second has passed
        if (System.currentTimeMillis() > time + 1000) {
            glfwSetWindowTitle(handle, title + " | FPS: " + frames);
            time = System.currentTimeMillis();
            frames = 0;
        }
    }

    public void destroy() {
        glfwWindowShouldClose(handle);
        glfwDestroyWindow(handle);
        glfwTerminate();
    }

    public void swapBuffers(){
        glfwSwapBuffers(handle);
    }

    public boolean shouldClose(){
        return glfwWindowShouldClose(handle);
    }

    public void setBackgroundColor(float r, float g, float b, float a){
        background.setX(r);
        background.setY(g);
        background.setZ(b);
        background.setW(a);
    }

}
