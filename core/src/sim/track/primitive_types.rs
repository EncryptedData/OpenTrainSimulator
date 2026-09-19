
pub type TrackId = u64;

pub type TrackConnection = Option<TrackId>;

pub type TrackBlockId = u64;

/// What is the status of the signal block
pub enum TrackBlockStatus {
    /// The block has a hazard, or the state is unknown
    Fault,

    /// The block is currently occupied by something
    Occupied,

    /// Nothing is currently occupying the block and it's ready
    Clear,
}