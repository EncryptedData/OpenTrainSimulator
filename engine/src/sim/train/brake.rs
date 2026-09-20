use crate::sim::physics::types::{Force, Percentage};

pub trait Brake {

    fn get_is_applied(&self) -> bool;

    fn get_percentage_active(&self) -> Percentage;

    fn get_breaking_force(&self) -> Force;

    fn activate_brake(&mut self, percentage: Percentage);
}