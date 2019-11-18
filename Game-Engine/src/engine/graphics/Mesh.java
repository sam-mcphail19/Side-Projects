package engine.graphics;

import org.lwjgl.opengl.GL11;
import org.lwjgl.opengl.GL15;
import org.lwjgl.opengl.GL20;
import org.lwjgl.opengl.GL30;
import org.lwjgl.system.MemoryUtil;

import java.nio.FloatBuffer;
import java.nio.IntBuffer;

public class Mesh {
    private Vertex[] vertices;
    private int[] indices; // which order to draw each vertex
    private int vertexArray, pixelBuffer, indexBuffer;

    public Mesh(Vertex[] vertices, int[] indices){
        this.vertices = vertices;
        this.indices = indices;
    }

    public void create(){
        vertexArray = GL30.glGenVertexArrays();
        GL30.glBindVertexArray(vertexArray);

        FloatBuffer positionBuffer = MemoryUtil.memAllocFloat(vertices.length * 3);
        float[] positionData = new float[vertices.length * 3];

        for(int i=0; i<vertices.length; i++){
            positionData[i*3] = vertices[i].getPosition().getX();
            positionData[i*3 + 1] = vertices[i].getPosition().getY();
            positionData[i*3 + 2] = vertices[i].getPosition().getZ();
        }

        positionBuffer.put(positionData).flip();

        pixelBuffer = GL15.glGenBuffers();
        GL15.glBindBuffer(GL15.GL_ARRAY_BUFFER, pixelBuffer);
        GL15.glBufferData(GL15.GL_ARRAY_BUFFER, positionBuffer, GL15.GL_STATIC_DRAW);
        GL20.glVertexAttribPointer(0, 3, GL11.GL_FLOAT, false, 0, 0);
        GL15.glBindBuffer(GL15.GL_ARRAY_BUFFER, 0);

        IntBuffer indicesBuffer = MemoryUtil.memAllocInt(indices.length);
        indicesBuffer.put(indices).flip();

        indexBuffer = GL15.glGenBuffers();
        GL15.glBindBuffer(GL15.GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        GL15.glBufferData(GL15.GL_ELEMENT_ARRAY_BUFFER, indicesBuffer, GL15.GL_STATIC_DRAW);
        GL15.glBindBuffer(GL15.GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    public Vertex[] getVertices() {
        return vertices;
    }

    public int[] getIndices() {
        return indices;
    }

    public int getVertexArray() {
        return vertexArray;
    }

    public int getPixelBuffer() {
        return pixelBuffer;
    }

    public int getIndexBuffer() {
        return indexBuffer;
    }
}
