use crate::core::window::Window;

pub struct NullWindow {
    should_continue: bool
}

impl NullWindow {
    fn set_should_continue(&mut self, should_continue: bool) {
        self.should_continue = should_continue;
    }
}

impl Window for NullWindow {
    fn should_continue(&self) -> bool {
        self.should_continue
    }

    fn update(&mut self) {}

    fn display_message(&self, message: &str) {
    }
}