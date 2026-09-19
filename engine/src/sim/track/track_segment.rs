use crate::sim::track::primitive_types::{TrackConnection, TrackId};
use glam::Vec3;

pub trait TrackSegment {
    fn get_id(&self) -> TrackId;

    fn get_connections(&self) -> Vec<TrackConnection>;

    fn get_positions(&self) -> Vec<Vec3>;
}