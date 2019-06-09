# uGLyRenderer
uGLyRenderer is a 3d model renderer for viewing various 3d models on your screen. It uses my [uGLy engine](https://github.com/gkarpa/uGLyEngine) for the scene setup and manipulation, [Assimp](https://github.com/assimp/assimp) for the file loading and [GLFW](https://www.glfw.org/) as its window & input library.

It features an orbit camera that you can manipulate with your mouse, along with a custom FoV. The application also setups a fixed point light (represented with an icosahedron inside the /meshes/ subfolder) that shades the scene using Blinn-Phong lighting shaders (inside the /shaders/ subfolder).

##### Usage:
- To run it, download the .rar from the assets of any release and run uGLyRenderer.exe (note: You will need a gpu with drivers that support OpenGL 4.6, currently).
- To load a model, drag'n'drop an Assimp compatible model file (e.g. an .obj file) into the application window.
- To rotate the orbit camera, move the mouse while holding its left button.
- To adjust the camera's vertical Field of View, you can use the mouse scroll wheel.
- key Esc : Terminate the application.
- keys S, W : To move the camera backwards and forward, respectively.
- key R : Reset the camera and projection to their initial states.
- key F : Toggle between solid and wireframe rendering.
- key C : Toggle backface culling.

You can see some screenshots from it in action below.

![](https://github.com/gkarpa/screenshots/blob/master/urd2.png)
![](https://github.com/gkarpa/screenshots/blob/master/urd1.png)
