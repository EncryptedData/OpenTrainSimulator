use std::ptr::null;
use sdl3::{Error, EventPump, Sdl, VideoSubsystem};
use sdl3::event::Event;
use sdl3::keyboard::Keycode;
use sdl3::messagebox::{show_simple_message_box, MessageBoxFlag};
use sdl3::render::WindowCanvas;
use engine::core::window::Window;

pub struct SDL3Window {
    context: Sdl,
    //window: sdl3::video::Window,
    event_pump: EventPump,
    should_continue: bool,

    canvas: WindowCanvas,
    video_subsystem: VideoSubsystem,
}

impl SDL3Window {

    pub fn new() -> Option<Self> {

        let context = match sdl3::init() {
            Ok(context) => context,
            Err(err) => return None,
        };

        let video_subsystem = match context.video() {
            Ok(sys) => sys,
            Err(err) => return None,
        };

        let window_result = video_subsystem.window("OpenTrainSimulator", 1280, 720)
            .position_centered()
            .resizable()
            .high_pixel_density()
            .build();

        let window = match window_result {
            Ok(window) => window,
            Err(err) => return None,
        };

        let canvas = window.into_canvas();

        let event_pump = match context.event_pump() {
            Ok(pump) => pump,
            Err(_) => return None,
        };

        Some(SDL3Window {
            should_continue: true,
            context,
            //window,
            event_pump,
            canvas,
            video_subsystem,
        })
    }
}

impl Window for SDL3Window {
    fn should_continue(&self) -> bool {
        self.should_continue
    }

    fn update(&mut self) {

        for event in self.event_pump.poll_iter() {
            match event {
                Event::Quit { .. } |
                Event::KeyDown { keycode: Some(Keycode::Escape), .. } => self.should_continue = false,
                _ => {}
            }
        }

        // For now just display a green screen
        self.canvas.set_draw_color(sdl3::pixels::Color::RGB(0, 255, 0));
        self.canvas.clear();
        self.canvas.present();

        // Just so we don't burn out the GPU rendering as fast as possible
        std::thread::sleep(std::time::Duration::from_millis(16));
    }

    fn display_message(&self, message: &str) {
        // TODO: Figure out how to display a simple message box
    }
}

