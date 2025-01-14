#include<SDL.hpp>

using namespace SDL;

SDL_HitTestResult hit_test(SDL_Window*, const SDL_Point* point, void*) {
    return SDL_HitTestResult(point->y < 50 ? HitTestResult::DRAGGABLE : HitTestResult::NORMAL);
}

int main() {
	Init();

	Input input;

	Mouse& mouse = input.mouse;

	Window w;
	Renderer r;
	Point& windowSize = input.windowSize = { 500, 500 };

	Rect rect(windowSize / 2 - Point(20, 20), { 40, 40 });
	CreateWindowAndRenderer(windowSize, w, r);

	w.SetTitle("Sample window");
	w.SetHitTest(hit_test, NULL);

	bool boxVisible = false;

	// Listeners are easier than Observers since they use lamdas/function objects rather than inheritence.
	// This is slower at runtime, but a lot faster to write.
	EventListener toggle_visibility = {[&](const Event& e) {
		if (e.button.button == (Uint8)Button::RIGHT)
			boxVisible = !boxVisible;
	}};
	input.RegisterTypedEventListener(Event::Type::MOUSEBUTTONDOWN, toggle_visibility);

    for (int frame [[maybe_unused]] = 0; input.running; frame++) {
		input.Update();

		if (mouse.GetButton(Button::LEFT))
			rect.pos = mouse.pos;

		r.SetDrawColour(VERY_DARK_BLUE).Clear();
		if(boxVisible) r.SetDrawColour(WHITE).FillRect(rect);
		r.SetDrawColour(VERY_LIGHT_AZURE).FillRect({ 0, 0, windowSize.w, 50 });

		r.Present();

		Delay(16);
	}
	Quit();

	w.SetHitTest(NULL, NULL);

	return 0;
}
