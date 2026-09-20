use engine::core::game_engine::GameEngine;
use crate::sdl3_window::SDL3Window;

pub mod sdl3_window;



fn main() {

    let sdl3_window = match SDL3Window::new() {
        Some(window) => Box::new(window),
        None => return,
    };

    let mut engine = GameEngine::new(sdl3_window);
    engine.run();
}
