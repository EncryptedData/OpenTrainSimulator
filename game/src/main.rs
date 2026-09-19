use sdl3::event::Event;
use sdl3::keyboard::Keycode;

fn main() {
    let sdl_context = sdl3::init().unwrap();

    let video_subsystem = sdl_context.video().unwrap();


    let window = video_subsystem.window("OpenTrainSimulator", 1280, 720)
        .position_centered()
        .resizable()
        .high_pixel_density()
        .build()
        .unwrap();

    let mut canvas = window.into_canvas();

    let mut event_pump = sdl_context.event_pump().unwrap();

    'main: loop {

        for event in event_pump.poll_iter() {
            match event {
                Event::Quit { .. } |
                Event::KeyDown { keycode: Some(Keycode::Escape), .. } => break 'main,
                _ => {}
            }
        }

        canvas.set_draw_color(sdl3::pixels::Color::RGB(0, 255, 0));
        canvas.clear();
        canvas.present();
        ::std::thread::sleep(std::time::Duration::from_millis(16));
    }

    println!("Hello, world!");
}
