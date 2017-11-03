inline void SRU(void) {
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_LIGHTING); //TODO: [D] FixMe: check if lighting and texture is enabled

	// eixo x
	glColor3f(1.0f, 0.0f, 0.0f);
	glLineWidth(1.0f);
	glBegin( GL_LINES );
        glVertex2f( -200.0f, 0.0f );
        glVertex2f(  200.0f, 0.0f );
	glEnd();

	// eixo y
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin( GL_LINES);
        glVertex2f(  0.0f, -200.0f);
        glVertex2f(  0.0f,  200.0f );
  	glEnd();
}
