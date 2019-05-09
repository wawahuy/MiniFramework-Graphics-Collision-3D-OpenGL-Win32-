//#define YUH_FREE_CONSOLE
#include <System/YuhSystem.h>
#include <Window/YuhWindow.h>
#include <Network/YuhNetwork.h>
#include <Graphics/YuhGraphics.h>
#include <Math/YuhMath.h>

using namespace yuh;
using namespace yuh::net;
using namespace yuh::window;
using namespace yuh::graphics;
using namespace yuh::math;

void calcFPS(const WindowPtr& window) {
	static Timer time2;
	static int f = 0;
	if (time2.elapsed() > 1000) {
		window->setTitile(L"OpenGL    FPS: " + std::to_wstring(f) + L"    -  Time: " + std::to_wstring((int)time2.elapsed()));
		time2.reset();
		f = 0;
	}
	f++;
}

void renderScene(Shader *shader);
void renderQuad();



// config size window
// ------------------
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

SkyBox *skybox;
Shader *shader;
Shader *shaderInstancing;
Texture *planeTexture;

Mat4f projection;
Camera camera;


int main() {
	//yuh
	ContextSetting setting;
	setting.cColorBits = 32;
	setting.cDepthBits = 24;
	setting.Samples = 4;

	WindowPtr window = Window::create(L"Test OpenGL", Vec2ui(SCR_WIDTH, SCR_HEIGHT), setting);
	window->getContext()->setGLActive(true);
	window->setFrameMax(60);
	window->getContext()->viewport(0, 0, 1000, 600);
	window->setMousePosition(Vec2i(200, 200));
	window->setPosition(Vec2i(50, 10));

	// matrix & config
	// ------
	projection = Perspective(45.0f, SCR_WIDTH, SCR_HEIGHT, 0.01, 1000);
	camera = Camera(Vec3f(0, 2.5, 5), Vec3f(0,0,-1));


	// Create sky box 
	PathSkyBox pathSky;
	pathSky.back	= "skybox/back.jpg";
	pathSky.bottom	= "skybox/bottom.jpg";
	pathSky.front	= "skybox/front.jpg";
	pathSky.left	= "skybox/left.jpg";
	pathSky.right	= "skybox/right.jpg";
	pathSky.top		= "skybox/top.jpg";

	skybox = new SkyBox();
	skybox->setMultiTexture(pathSky);
	skybox->setProjection(projection);


	// shader
	// -------
	shader = new Shader();
	shaderInstancing = new Shader();
	shader->setWithFile(FileInputStream("glsl/shader.vert"), FileInputStream("glsl/shader.frag"));
	shaderInstancing->setWithFile(FileInputStream("glsl/shaderInstancing.vert"), FileInputStream("glsl/shaderInstancing.frag"));
	
	// texture
	// ---------
	planeTexture = new Texture();
	planeTexture->set("texture/cc.jpg");

	// enable
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// time
	// ------
	Timer timer;

	float moveFront = 0;
	float moveSide = 0;
	Vec2f pitchYaw;

	// center mouse
	while (window->isOpen()) {

#pragma region Event And Mouse, Key
		Event evt;
		while (window->pollEvent(evt)) {
			
			if (evt == Event::Closed) {
				window->close();
			}

			if (evt == Event::Resize) {
				Vec2ui size = window->getSize();
				window->getContext()->viewport(0, 0, size.x, size.y);
			}

			if (evt == Event::MouseMove) {
			
				if (!window->isMouseCenterWindow()) window->setMouseCenterWindow();
				
				Vec2i c = evt.mouse - window->getMouseCenterWindow();

				if (c.y != 0) {
					pitchYaw.x = -c.y / abs(c.y);
				}

				if (c.x != 0) {
					pitchYaw.y = c.x / abs(c.x);
				}
			}

			if (evt == Event::KEY_PRESSED) {
				if (evt.key == 'W') moveFront = -1;
				if (evt.key == 'S') moveFront =  1;
				if (evt.key == 'A') moveSide = -1;
				if (evt.key == 'D') moveSide =  1;
			}
			
			if (evt == Event::KEY_RELEASE) {
				if (evt.key == 'W') moveFront = 0;
				if (evt.key == 'S') moveFront = 0;
				if (evt.key == 'A') moveSide = 0;
				if (evt.key == 'D') moveSide = 0;
			}
		}


		// update fps camera
		// ----------------------
		float factor = 0.0025;
		if (pitchYaw.x != 0) {
			camera.pitch(pitchYaw.x*factor*timer.elapsed());
			pitchYaw.x /= 2;
		}
		if (pitchYaw.y != 0) {
			camera.yaw(pitchYaw.y*factor*timer.elapsed());
			pitchYaw.y /= 2;
		}

		float speed = 0.01;
		if (moveFront != 0) {
			Vec3f dir = camera.getDirection();
			dir.y = 0;
			camera.translate(dir*float(-moveFront*speed*timer.elapsed()));
		}

		if (moveSide != 0) {
			Vec3f right = camera.getRight();
			right.y = 0;
			camera.translate(right*float(moveSide*speed*timer.elapsed()));
		}
		timer.reset();
#pragma endregion


		// repaint scene
		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//render sky
		skybox->setCamera(camera);
		skybox->draw();

		//render scene & shadow
		shader->bind();
		shader->uniformMat4f("projection", projection);
		shader->uniformMat4f("view", camera.getMatrixView());
		shader->uniform("view_position", camera.getPosition());
		renderScene(shader);
		

		// debug scene , view axis y
		glViewport(SCR_WIDTH*0.7, SCR_HEIGHT*0.7, SCR_WIDTH*0.2, SCR_HEIGHT*0.2);
		Mat4f OProj = Ortho(-55, 55, -55, 55, -10, 50);
		Camera OView;
		OView.setPosition(Vec3f(0, 5, 0));
		OView.setDirection(Vec3f(0.01, -1, 0));
		shader->uniformMat4f("projection", OProj);
		shader->uniformMat4f("view", OView.getMatrixView());
		shader->uniform("view_position", OView.getPosition());
		renderScene(shader);

		// calc FPS
		// --------
		calcFPS(window);


		// swap buffer & limit fps
		// ----------
		window->display();
	}

	return 0;
}



void renderPlane(Shader *shader) {
	static Mesh plane;
	static bool tb = true;

	if (tb) {
		tb = false;
		// set up vertex data (and buffer(s)) and configure vertex attributes
		// ------------------------------------------------------------------
		Vertex planeVertices[] = {
			//positions            // normals         // texcoords
			Vertex(Vec3f(50.0f, -0.5f,  50.0f),  Vec3f(0.0f, 1.0f, 0.0f),  Vec2f(50.0f,  0.0f)),
			Vertex(Vec3f(50.0f, -0.5f,  -50.0f),  Vec3f(0.0f, 1.0f, 0.0f),  Vec2f(0.0f,  0.0f)),
			Vertex(Vec3f(-50.0f, -0.5f, -50.0f), Vec3f(0.0f, 1.0f, 0.0f),   Vec2f(0.0f, 50.0f)),

			Vertex(Vec3f(50.0f, -0.5f,  50.0f),  Vec3f(0.0f, 1.0f, 0.0f),  Vec2f(50.0f,  0.0f)),
			Vertex(Vec3f(-50.0f, -0.5f, -50.0f), Vec3f(0.0f, 1.0f, 0.0f), Vec2f(0.0f, 50.0f)),
			Vertex(Vec3f(-50.0f, -0.5f, 50.0f),  Vec3f(0.0f, 1.0f, 0.0f), Vec2f(50.0f, 50.0f))
		};
		GLuint ind[] = {0,1,2,3,4,5};
		plane.set(planeVertices, 6, ind, 6);
	}

	plane.draw();
	plane.drawDebug();
}




// renders the 3D scene
// --------------------
void renderScene(Shader *shader)
{
	static bool iiint = false;
	static Model *modelXe;

	const size_t numXe = 10;
	static Model modelXes[numXe];


	if (!iiint) {
		modelXe = new Model();
		modelXe->LoadFromFile("obj/obj3/Models/OFF -Road car  3D Models (2).3DS");
		modelXe->setScale(Vec3f(0.01, 0.01, 0.01));
		modelXe->setRotate(Vec3f(-90 * 3.14 / 180, 0, 0));
		modelXe->setPosition(Vec3f(rand() % 100 - 50, 0.45, rand() % 100 - 50));

		for (int i = 0; i < numXe; i++) {
			modelXes[i] = *modelXe;
			modelXes[i].setScale(Vec3f(0.01, 0.01, 0.01));
			modelXes[i].setRotate(Vec3f(-90 * 3.14 / 180, 0, 0));
			modelXes[i].setPosition(Vec3f(rand() % 100 - 50, 0.45, rand() % 100 - 50));
		}
		
		iiint = true;
	}


	planeTexture->bind();
	renderPlane(shader);

	

	// test frustum culling
	Frustum fr(projection, camera);

	fr.drawDebug();

	for (int i = 0; i < numXe; i++) {
		if (fr.testAABB(modelXes[i].getCoverAABB())) {
			modelXes[i].draw();
		}
	}

	for (int i = 0; i < numXe; i++) {
			modelXes[i].drawDebug();
	} 

}


// renderQuad() renders a 1x1 XY quad in NDC
// -----------------------------------------
unsigned int quadVAO = 0;
unsigned int quadVBO;
void renderQuad()
{
	if (quadVAO == 0)
	{
		float quadVertices[] = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		// setup plane VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}