use crate::core::window::Window;

pub struct GameEngine{
    window: Box<dyn Window>,
}

impl GameEngine {
    pub fn new(window: Box<dyn Window>) -> GameEngine {
        GameEngine {
            window,
        }
    }

    pub fn run(&mut self) {
        while self.window.should_continue() {
            self.do_tick();
        }
    }

    fn do_tick(&mut self) {
        self.window.update();
    }
}