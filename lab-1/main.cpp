#include <iostream>
#include <functional>
#include <array>
#include <fstream>
#include <sstream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Events.h"
#include "Shader.h"
#include "Mesh.h"
#include "Renderer.h"

using Callback = std::function<void()>;

/// \n Struct used to debug shader creation.
struct glStatusData {
	/// \n Indicates whether the shader creation was successful.
	int success;
	/// \n The name given to the shader.
	const char* shaderName;
	/// \n Log messages attributed to the current shader.
	char infoLog[GL_INFO_LOG_LENGTH];
};

struct Entity {
public:
	Entity(const std::vector<glm::vec3>& vertices, const std::vector<unsigned int>& indices, const glm::vec4& color) : 
		mesh(vertices, indices), renderer(color) {};
	Mesh mesh;
	Renderer renderer;
};

// Variable declaration
GLFWwindow* window = nullptr; 
Event* update = nullptr;
Shader* shader = nullptr;

GLuint VAO = 0;
std::vector<Entity> entities = {};

// Shader Functions- click on + to expand
#pragma region SHADER_FUNCTIONS
inline fs::path resolveAssetPath(const fs::path& relativeAssetPath) {
	auto mergedPath = (fs::current_path() / relativeAssetPath).make_preferred();
	return fs::canonical(mergedPath);
}

std::string ReadText(const fs::path& path) {
	std::ifstream sourceFile(resolveAssetPath(path));
	std::stringstream buffer;
	buffer << sourceFile.rdbuf();
	return buffer.str();
}

unsigned int LoadAndCompileShader(const GLuint& shaderType, const fs::path& filePath) {
	auto shaderID = glCreateShader(shaderType);
	auto shaderSource = ReadText(filePath);
	auto source = shaderSource.c_str();
	glShaderSource(shaderID, 1, &source, nullptr);
	glCompileShader(shaderID);

	glStatusData compilationStatus{};
	compilationStatus.shaderName = shaderType == GL_VERTEX_SHADER ? "Vertex" : "Fragment";
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compilationStatus.success);
	if (compilationStatus.success == GL_FALSE) {
		glGetShaderInfoLog(shaderID, GL_INFO_LOG_LENGTH, nullptr, compilationStatus.infoLog);
		std::string errorMessage = std::string(compilationStatus.shaderName) + 
			" shader compilation failed.\n" + std::string(compilationStatus.infoLog);
		throw std::exception(errorMessage.c_str());
	}

	return shaderID;
}
#pragma endregion SHADER_FUNCTIONS

#pragma region rendering
static void InitRenderingSystem() {
	glGenVertexArrays(1, &VAO);

	shader = new Shader(
		LoadAndCompileShader(GL_VERTEX_SHADER, Shader::defaultVertexShaderPath), 
		LoadAndCompileShader(GL_FRAGMENT_SHADER, Shader::defaultFragmentShaderPath));
}

void display(Entity& entity){
	glEnable(GL_DEPTH_TEST);
	auto vpMatrix = glm::mat4(1);

	auto* activeShader = shader;
	glBindVertexArray(VAO);
	activeShader->Apply(vpMatrix);

	auto model = glm::mat4(1);
	activeShader->setMatrix("mvp", activeShader->CalculateMVPMatrix(model));
	auto renderer = &entity.renderer;
	if (renderer)
		renderer->ApplyData(*activeShader);
	entity.mesh.draw();
}
#pragma endregion

#pragma region context
static void InitGLFW() {
	if (!glfwInit())
		throw std::exception("GL ERROR: Failed to initialize GLFW!");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }

static void CreateWindow(const std::string& title) {
	auto* monitor = glfwGetPrimaryMonitor();
	auto* mode = glfwGetVideoMode(monitor);
	window = glfwCreateWindow(mode->width, mode->height, title.c_str(), nullptr, nullptr);

	if (window == nullptr)
		throw std::exception("GL ERROR: Failed to create window.");

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

static void LoadGlad() {
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (glGetError() != GL_NO_ERROR)
		throw std::exception("GL Error - Failed to load GLAD");
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

static void run(const Callback& update) {
	glfwSetTime(1.0 / 60);
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.1608f, 0.5725f, 0.7804f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		update();
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}
#pragma endregion

static void init()
{
	// Create 3 vertices that make up a triangle that fits on the viewport 
	std::vector<glm::vec3> vertices = {
		glm::vec3(- 1.0f, -1.0f, 0.0f),
		glm::vec3(1.0f, -1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(2.0f, 1.0f, 0.0f)
	};

	std::vector<unsigned int> indices = {
		0, 1, 2,
		1, 3, 2
	};

	// Create a color array that identfies the colors of each vertex (format R, G, B, A)
	std::vector<glm::vec4> colors = {
		glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
		glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)
	};

	Entity e = Entity(vertices, indices, colors[0]);
	entities.emplace_back(e);
}

int main(){
	std::cout << "Hello World!";
	
	// create window
	InitGLFW();
	CreateWindow("Hello Triangle!");
	LoadGlad();

	// Set up your objects and shaders
	update = new Event();
	InitRenderingSystem();
	init();

	update->addListener([&]() {for (Entity& entity : entities) { display(entity); }});

	// Begin infinite event loop
	run([&]() {update->invoke();});
    return 0;
}











