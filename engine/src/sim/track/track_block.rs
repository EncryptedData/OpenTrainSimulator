use std::cmp::PartialEq;

#[derive(PartialEq)]
pub enum TrackBlockHazardType {
    Railcar,
    DerailedRailcar,
    EnvironmentalHazard,
    Unknown,
}

/// What is the status of the signal block
pub enum TrackBlockStatus {
    /// The block has a hazard, or the state is unknown
    Fault,

    /// The block is currently occupied by something
    Occupied,

    /// Nothing is currently occupying the block and it's ready
    Clear,
}

pub struct TrackBlock {
    hazards: Vec<TrackBlockHazardType>,
}

impl TrackBlock {
    pub fn new() -> Self {
        Self {
            hazards: Vec::new(),
        }
    }

    pub fn get_status(&self) -> TrackBlockStatus {
        if self.hazards.is_empty() {
            TrackBlockStatus::Clear
        } else {
            if self.hazards.iter().any(|x: &TrackBlockHazardType| { *x != TrackBlockHazardType::Railcar }) {
                TrackBlockStatus::Fault
            }
            else {
                TrackBlockStatus::Occupied
            }
        }
    }

    pub fn set_hazard(&mut self, hazard_type: TrackBlockHazardType) {
        self.hazards.push(hazard_type);
    }

    pub fn remove_hazard(&mut self, hazard_type: TrackBlockHazardType) {
        self.hazards.retain(|h| h != &hazard_type);
    }
}