//////////////////////////////////////////////////////////////////////
// Yet Another Tibia Client
//////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//////////////////////////////////////////////////////////////////////

/// \file enginegl.cpp
///
/// Contains the code for OpenGL rendering engine.
///
/// \sa EngineGL

#include <GL/gl.h>
#include "enginegl.h"

EngineGL::EngineGL()
{
	printf("Starting OpenGL engine\n");
	m_videoflags = SDL_OPENGL | SDL_RESIZABLE;

	m_screen = SDL_SetVideoMode(m_width, m_height, m_video_bpp, m_videoflags);

	if(!m_screen){
		fprintf(stderr, "Could not set %dx%d video mode: %s\n", m_width, m_height, SDL_GetError());
		return;
		//exit(1);
	}

	m_sysfont->SetFontParam(createSprite("font.bmp"));

	initEngine();
	doResize(m_width, m_height);
}

EngineGL::~EngineGL()
{
	SDL_FreeSurface(m_screen);
	delete (SpriteGL*)m_sysfont->GetFontParam();
	printf("Closing OpenGL engine\n");
}

void EngineGL::initEngine()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void EngineGL::doResize(int w, int h)
{
	Engine::doResize(w, h);

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, w, h, 0.0f, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void EngineGL::drawRectangle(float x, float y, float width, float height, oRGBA color)
{
	glDisable(GL_TEXTURE_2D);

	glColor4f(color.r/255.0f, color.g/255.0f, color.b/255.0f, color.a/255.0f);

	glRectf(x, y, x+width, y+height);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

bool EngineGL::isSupported() {

	if (!m_screen) return false; else return true;
	/*uint32_t vf = SDL_OPENGL | SDL_RESIZABLE;

	SDL_Surface *s = SDL_SetVideoMode(m_width, m_height, m_video_bpp, m_videoflags);
	if (s) {
		SDL_FreeSurface(s);
		return true;
	} else
		return false;*/
}
