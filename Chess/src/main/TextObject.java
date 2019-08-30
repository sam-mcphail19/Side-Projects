package main;

import java.awt.*;

public class TextObject extends GameObject{

	String value;
	int fontSize;
	String font;

	public TextObject(int x, int y, int fontSize, String font, String value) {

		super(x, y);
		this.fontSize = fontSize;
		this.value = value;
		this.font = font;

	}

	public void tick() { }

	public void render(Graphics g) {

		Graphics2D g2 = (Graphics2D) g;
		g2.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING, RenderingHints.VALUE_TEXT_ANTIALIAS_ON);

		g2.setColor(Color.WHITE);
		g2.setFont(new Font(font, Font.BOLD, fontSize));
		g2.drawString(value, x, y);

	}

	public void setValue(String value) {
		this.value = value;
	}

	public String getValue(){
		return this.value;
	}


}
