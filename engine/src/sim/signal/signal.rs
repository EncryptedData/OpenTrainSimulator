use crate::sim::signal::primitive_types::SignalId;

pub trait Signal {
    fn get_id(&self) -> SignalId;
}