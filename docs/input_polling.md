## Input polling:
The input polling system in MoonlightVxl is made up of 2 classes: vxl::GlobalInput, and vxl::Input.

The vxl::Input class contains two arrays of _booleans_, while one represents the keys and the other the mouse buttons. The keycode/mouse button id is used as the index when accessing an element of the array.

The global input system only stores the position of the mouse (relative to the upper-left corner of the window) and doesn't store the state of the keys/mouse buttons, but actually just gets the key/mouse button state from glfw3. 
Another difference between the two is that vxl::GlobalInput is totally static.

The local version is used in MoonlightVxl's layer system by every vxl::Layer having an instance of vxl::Input.

### Global input:
Examples of global input being used:
```cpp
void MyApp::update() override {
    if (vxl::GlobalInput::get_key(GLFW_KEY_F))
        printf("Respect has been paid.\n");
    if (vxl::GlobalInput::get_mouse_button(GLFW_MOUSE_BUTTON_1))
        printf("You clicked the cookie.\n");
	auto [x, y] = vxl::GlobalInput::get_mouse_position(); // C++17 structured bindings
	if (x == 69.0f && y == 420.0f)
		printf("Nice.\n");
}
```
The get_mouse_position function is also overloaded to accept 2 references of doubles as a parameter, if the client doesn't want to use structured bindings
```cpp
	double x, y;
	vxl::GlobalInput::get_mouse_position(x, y);
	if (x == 69.0f && y == 420.0f)
		printf("Nice.\n");
```

### Local input:
Used in the layer system but can be completely ignored by overriding it's on_event function, or used in something else if you wish.

By default, whenever a KeyPressedEvent is sent to a layer (by the on_event function), the _boolean_ corresponding to the specific key in the layer's instance of vxl::Input is set to true, and only set to false when a KeyReleasedEvent is sent to the layer with the same keycode.

If you wish to override the on_event function and still use the local input system, just add the original on_event as a decorator on your function.
Example:
```cpp
void MyLayer::on_event(vxl::Event& e) override {
    vxl::Layer::on_event(e);
    // your code
}
```

Examples of local input being used:
```cpp
void MyLayer::update() override {
	if (input.get_key(GLFW_KEY_F))
		printf("Respect has been paid.\n");
	if (input.get_mouse_button(GLFW_MOUSE_BUTTON_1))
       	printf("You clicked the cookie.\n");
}
```
or
```cpp
void MyLayer::update() override {
	if (input.get_keys()[GLFW_KEY_F])
        printf("Respect has been paid.\n");
    if (input.get_mouse_buttons()[GLFW_MOUSE_BUTTON_1])
        printf("You clicked the cookie.\n");
}
```

### Manually setting values
Here's an example for setting the value of a key and a mouse button in the local input polling system:
```cpp
MyLayer::MyLayer() : vxl::Layer() {
	input.set_key(GLFW_KEY_W, true);
	input.set_mouse_button(GLFW_MOUSE_BUTTON_2, false);
}

void MyLayer::on_event(vxl::Event& e) override {
	switch (e.get_event_type()) {
		case EventType::KeyPressed: {
			input.get_keys()[_GET_EVENT_KEYCODE(e)] = true;
			break;
		}
		case EventType::KeyReleased: {
			input.get_key(_GET_EVENT_KEYCODE(e)) = false;
			break;
		}
		case EventType::MouseButtonPressed: {
			input.get_mouse_buttons()[_GET_EVENT_MOUSE_BUTTON(e)] = true;
			break;
		}
		case EventType::MouseButtonReleased: {
			input.get_mouse_button(_GET_EVENT_MOUSE_BUTTON(e)) = false;
			break;
		}
	}
}
```