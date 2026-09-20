
pub trait Window {
    
    fn should_continue(&self) -> bool;
    
    fn update(&mut self);
    
    fn display_message(&self, message: &str);
}