package engine.graphics;

import org.lwjgl.opengl.GL11;
import org.lwjgl.opengl.GL13;
import org.lwjgl.opengl.GL15;
import org.lwjgl.opengl.GL20;
import org.lwjgl.opengl.GL30;


public class Renderer {
    private void renderMesh(Mesh mesh) {
        Image image = mesh.getImage();

        GL11.glEnable(GL11.GL_BLEND);
        GL11.glBlendFunc(GL11.GL_SRC_ALPHA, GL11.GL_ONE_MINUS_SRC_ALPHA);

        GL30.glBindVertexArray(mesh.getVAO());
        GL20.glEnableVertexAttribArray(0);
        GL20.glEnableVertexAttribArray(1);
        GL20.glEnableVertexAttribArray(2);
        GL15.glBindBuffer(GL15.GL_ELEMENT_ARRAY_BUFFER, mesh.getIBO());
        if(image != null){
            image.loadTexture();
            GL13.glActiveTexture(GL13.GL_TEXTURE0);
            GL11.glBindTexture(GL11.GL_TEXTURE_2D, image.getTextureID());
        }
        GL11.glDrawElements(GL11.GL_TRIANGLES, mesh.getIndices().length, GL11.GL_UNSIGNED_INT, 0);
        GL15.glBindBuffer(GL15.GL_ELEMENT_ARRAY_BUFFER, 0);
        GL20.glDisableVertexAttribArray(0);
        GL20.glDisableVertexAttribArray(1);
        GL20.glDisableVertexAttribArray(2);
        GL30.glBindVertexArray(0);
        GL11.glDisable(GL11.GL_BLEND);
    }

    public void renderMeshWireFrame(Mesh mesh){
        GL11.glPolygonMode(GL11.GL_FRONT, GL11.GL_LINE);
        GL11.glPolygonMode(GL11.GL_BACK, GL11.GL_LINE);
        renderMesh(mesh);
    }

    public void renderMeshFill(Mesh mesh){
        GL11.glPolygonMode(GL11.GL_FRONT, GL11.GL_FILL);
        GL11.glPolygonMode(GL11.GL_BACK, GL11.GL_FILL);
        renderMesh(mesh);
    }

}
