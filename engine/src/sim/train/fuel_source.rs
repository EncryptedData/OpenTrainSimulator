use crate::sim::physics::types::Percentage;

pub type FuelUnit = f32;

pub struct FuelSource {
    maximum_capacity: FuelUnit,
    current_capacity: FuelUnit,
    consumption_rate: FuelUnit,
}

impl FuelSource {
    pub fn new(maximum_capacity: FuelUnit, current_capacity: FuelUnit) -> Option<Self> {

        if !f32::is_finite(maximum_capacity) || !f32::is_finite(current_capacity) {
            return None;
        }

        if maximum_capacity < 0.0 || current_capacity < 0.0 {
            return None;
        }

        if current_capacity > maximum_capacity {
            return None;
        }

        Some(Self{
            maximum_capacity,
            current_capacity,
            consumption_rate: 0.0,
        })
    }

    pub fn maximum_capacity(&self) -> FuelUnit {
        self.maximum_capacity
    }

    pub fn current_capacity(&self) -> FuelUnit {
        self.current_capacity
    }

    pub fn capacity_percentage(&self) -> Percentage {
        self.current_capacity / self.maximum_capacity
    }

    pub fn is_empty(&self) -> bool {
        self.current_capacity == 0.0
    }

    pub fn is_full(&self) -> bool {
        self.current_capacity == self.maximum_capacity
    }

    pub fn current_consumption_rate(&self) -> FuelUnit {
        self.consumption_rate
    }

    pub fn set_current_consumption_rate(&mut self, rate: FuelUnit) {
        self.consumption_rate = rate;
    }

    pub fn add_fuel(&mut self, amount: FuelUnit) -> bool {
        self.current_capacity += amount;

        if self.current_capacity > self.maximum_capacity {
            self.current_capacity = self.maximum_capacity;
            false
        } else {
            true
        }
    }

    pub fn set_fuel(&mut self, amount: FuelUnit) -> bool {
        if f32::is_sign_negative(amount) || !f32::is_finite(amount) {
            return false;
        }

        self.current_capacity = amount;

        if self.current_capacity > self.maximum_capacity {
            self.current_capacity = self.maximum_capacity;
            false
        } else {
            true
        }
    }

    pub fn consume(&mut self) -> bool {
        if self.can_consume() {
            self.current_capacity -= self.consumption_rate;
            true
        } else {
            false
        }
    }

    pub fn can_consume(&self) -> bool {
        self.current_capacity - self.consumption_rate >= 0.0
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn cannot_consume_with_empty_capacity() {
        let mut fuel_source = FuelSource::new(10.0, 0.0).unwrap();
        fuel_source.set_current_consumption_rate(1.0);
        assert!(!fuel_source.can_consume());
        assert!(!fuel_source.consume());

        assert_eq!(fuel_source.current_capacity, 0.0);
    }
}