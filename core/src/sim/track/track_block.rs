use crate::sim::track::primitive_types::TrackBlockStatus;

trait TrackBlock {
    fn get_status(&self) -> TrackBlockStatus;

    fn set_status(&mut self, status: TrackBlockStatus);
}