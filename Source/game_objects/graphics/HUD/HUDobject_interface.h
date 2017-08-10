#pragma once

#include "../../../util/graphics/gl.h"

#include "../../../Game.h"
#include "../GraphicsObjectManager.h"

// TODO: Rename to just HUDobject, seeing that it's more of an abstract class..?
class HUDobject_interface
{
protected:
	GLuint m_vertexArrayObject;

	GLint m_vertexData_uniformIndex;
	GLfloat m_vertexData[4 * 2 + 4 * 2];

protected:
	/* User should call setCoords() after calling this constructor. */
	HUDobject_interface(GLuint program, const GraphicsObjectManager& graphicsObjectManager);

	HUDobject_interface(GLuint program, const GraphicsObjectManager& graphicsObjectManager, GLfloat xPos, GLfloat yPos, GLfloat width, GLfloat height);

public:
	virtual ~HUDobject_interface() {}

public:
	virtual void graphicsUpdate(GLuint program, const GraphicsObjectManager& graphicsObjectManager);

protected:
	/*
	xPos and yPos are the coordinates of the image's lower left corner.
	width and height are the image's dimensions measured in pixels.
	*/
	virtual void setCoords(GLfloat xPos, GLfloat yPos, GLfloat width, GLfloat height) { _setCoords(xPos, yPos, width, height, m_vertexData); }

	virtual GLfloat getWidth() const { return _getWidth(m_vertexData); }
	virtual GLfloat getHeight() const { return _getHeight(m_vertexData); }

	virtual void setWidth(GLfloat width, bool preserveAspectRatio) { _setWidth(width, preserveAspectRatio, m_vertexData); }
	virtual void setHeight(GLfloat height, bool preserveAspectRatio) { _setHeight(height, preserveAspectRatio, m_vertexData); }

	virtual void move(GLfloat xDirection, GLfloat yDirection) { _move(xDirection, yDirection, m_vertexData); }

	/* xPos and yPos are the coordinates of the image's lower left corner. */
	virtual void moveTo(GLfloat xPos, GLfloat yPos) { _moveTo(xPos, yPos, m_vertexData); }

	/*
	Set newWidth or newHeight to -1 to make the image maintain its aspect ratio during the zoom.
	focusX and focusY are relative to the window's lower left corner, and are clamped between 0 and 1.
	*/
	virtual void zoom(GLfloat newWidth, GLfloat newHeight, GLfloat focusX = 0.5f, GLfloat focusY = 0.5f) { _zoom(newWidth, newHeight, focusX, focusY, m_vertexData); }

protected:
	static void _setCoords(GLfloat xPos, GLfloat yPos, GLfloat width, GLfloat height, GLfloat vertexData[8]);

	constexpr static GLfloat _getWidth(const GLfloat vertexData[8]) { return vertexData[2] - vertexData[0]; }
	constexpr static GLfloat _getHeight(const GLfloat vertexData[8]) { return vertexData[5] - vertexData[3]; }

	static void _setWidth(GLfloat width, bool preserveAspectRatio, GLfloat vertexData[8]);
	static void _setHeight(GLfloat height, bool preserveAspectRatio, GLfloat vertexData[8]);
	static void _move(GLfloat xDirection, GLfloat yDirection, GLfloat vertexData[8]);
	static void _moveTo(GLfloat xPos, GLfloat yPos, GLfloat vertexData[8]);
	static void _zoom(GLfloat newWidth, GLfloat newHeight, GLfloat focusX, GLfloat focusY, GLfloat vertexData[8]);
};
