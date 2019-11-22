package engine.graphics;

import org.lwjgl.opengl.*;


public class Renderer {
    private void renderMesh(Mesh mesh) {
        Image image = mesh.getImage();
        image.loadTexture();
        GL30.glBindVertexArray(mesh.getVAO());
        GL20.glEnableVertexAttribArray(0);
        GL20.glEnableVertexAttribArray(1);
        GL20.glEnableVertexAttribArray(2);
        GL15.glBindBuffer(GL15.GL_ELEMENT_ARRAY_BUFFER, mesh.getIBO());
        GL13.glActiveTexture(GL13.GL_TEXTURE0);
        GL11.glBindTexture(GL11.GL_TEXTURE_2D, image.getTextureID());
        GL11.glDrawElements(GL11.GL_TRIANGLES, mesh.getIndices().length, GL11.GL_UNSIGNED_INT, 0);
        GL15.glBindBuffer(GL15.GL_ELEMENT_ARRAY_BUFFER, 0);
        GL20.glDisableVertexAttribArray(0);
        GL20.glDisableVertexAttribArray(1);
        GL20.glDisableVertexAttribArray(2);
        GL30.glBindVertexArray(0);
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
