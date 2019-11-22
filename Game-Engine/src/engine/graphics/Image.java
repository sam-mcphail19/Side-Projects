package engine.graphics;

import Main.Main;
import org.lwjgl.BufferUtils;
import org.lwjgl.opengl.GL11;
import org.lwjgl.opengl.GL12;
import org.lwjgl.stb.STBImage;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.IntBuffer;
import java.nio.channels.FileChannel;

import static org.lwjgl.system.jemalloc.JEmalloc.je_malloc;

public class Image {

    private ByteBuffer image;
    private final int width, height;
    private int textureID;

    public Image(ByteBuffer image, int width, int height) {
        this.image = image;
        this.width = width;
        this.height = height;
    }

    public static Image create(String path){
        ByteBuffer imageBuffer;

        try {
            imageBuffer = fileToByteBuffer(path);
        } catch(IOException e) {
            System.err.println("Could not find the image at the path '" + path + "'");
            e.printStackTrace();
            return null;
        }

        IntBuffer width = BufferUtils.createIntBuffer(1);
        IntBuffer height = BufferUtils.createIntBuffer(1);
        IntBuffer components = BufferUtils.createIntBuffer(1);

        ByteBuffer image = STBImage.stbi_load_from_memory(imageBuffer, width, height, components, 0);

        return new Image(image, width.get(0), height.get(0));
    }

    public void destroy() {
        STBImage.stbi_image_free(image);
    }

    public static ByteBuffer fileToByteBuffer(String path) throws IOException {
        ByteBuffer buffer;

        File file = new File(path);
        FileInputStream fis = new FileInputStream(file);
        FileChannel fc = fis.getChannel();

        buffer = je_malloc((int) fc.size() + 1);

        //read the whole file into the buffer
        while(fc.read(buffer) != -1);

        fis.close();
        fc.close();

        buffer.flip();
        return buffer;
    }

    public void loadTexture() {

        image.flip();

        int textureID = GL11.glGenTextures(); //Generate texture ID
        GL11.glBindTexture(GL11.GL_TEXTURE_2D, textureID); //Bind texture ID

        //Setup wrap mode
        GL11.glTexParameteri(GL11.GL_TEXTURE_2D, GL11.GL_TEXTURE_WRAP_S, GL12.GL_CLAMP_TO_EDGE);
        GL11.glTexParameteri(GL11.GL_TEXTURE_2D, GL11.GL_TEXTURE_WRAP_T, GL12.GL_CLAMP_TO_EDGE);

        //Setup texture scaling filtering
        GL11.glTexParameteri(GL11.GL_TEXTURE_2D, GL11.GL_TEXTURE_MIN_FILTER, GL11.GL_NEAREST);
        GL11.glTexParameteri(GL11.GL_TEXTURE_2D, GL11.GL_TEXTURE_MAG_FILTER, GL11.GL_NEAREST);

        //Send texel data to OpenGL
        GL11.glTexImage2D(GL11.GL_TEXTURE_2D, 0, GL11.GL_RGBA8, getWidth(), getHeight(), 0, GL11.GL_RGBA, GL11.GL_UNSIGNED_BYTE, image);

        //Return the texture ID so we can bind it later again
        this.textureID = textureID;
    }

    public int getTextureID() {
        return textureID;
    }

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }

}