use glam::{Quat, Vec3};
use crate::sim::physics::types::Weight;
use crate::sim::train::brake::Brake;

pub trait Railcar {
    fn update(&mut self);

    fn is_self_powered(&self) -> bool;

    fn get_position(&self) -> Vec3;

    fn get_rotation(&self) -> Quat;

    fn get_weight(&self) -> Weight;

    fn get_brake(&mut self) -> &mut dyn Brake;
}