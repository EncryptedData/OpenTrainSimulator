use engine::sim::train::fuel_source::FuelSource;

#[test]
fn new_does_not_allow_negative_maximum_capacity() {
    assert!(FuelSource::new(-1.0, 0.0).is_none());
}

#[test]
fn new_does_not_allow_negative_current_capacity() {
    assert!(FuelSource::new(1.0, -1.0).is_none());
}

#[test]
fn new_maximum_capacity_must_be_finite_number() {
    assert!(FuelSource::new(f32::INFINITY, 0.0).is_none());
    assert!(FuelSource::new(f32::NAN, 0.0).is_none());
    assert!(FuelSource::new(f32::NEG_INFINITY, 0.0).is_none());
}

#[test]
fn new_current_capacity_must_be_finite_number() {
    assert!(FuelSource::new(10.0, 1.0).is_some());
    assert!(FuelSource::new(10.0, f32::INFINITY).is_none());
    assert!(FuelSource::new(10.0, f32::NAN).is_none());
    assert!(FuelSource::new(10.0, f32::NEG_INFINITY).is_none());
}

#[test]
fn new_maximum_capacity_must_be_bigger_than_current_capacity() {
    assert!(FuelSource::new(10.0, 11.0).is_none());
}

#[test]
fn new_works() {
    assert!(FuelSource::new(10.0, 10.0).is_some());
}

#[test]
fn maximum_capacity_works() {
    let capacity = 10.0;
    let fuel_source = FuelSource::new(capacity, 10.0).unwrap();
    
    assert_eq!(fuel_source.maximum_capacity(), capacity);
}

#[test]
fn current_capacity_works() {
    let capacity = 10.0;
    let fuel_source = FuelSource::new(capacity, capacity).unwrap();

    assert_eq!(fuel_source.maximum_capacity(), capacity);
}

#[test]
fn capacity_percentage_works() {
    for i in 0..100 {
        let fuel_source = FuelSource::new(100.0, i as f32).unwrap();
        assert_eq!(fuel_source.capacity_percentage(), i as f32 / 100.0);
    }
}

#[test]
fn is_empty_works() {
    let mut fuel_source = FuelSource::new(10.0, 10.0).unwrap();

    assert!(!fuel_source.is_empty());

    fuel_source.set_fuel(0.0);
    assert!(fuel_source.is_empty());
}

#[test]
fn is_full_works() {
    let mut fuel_source = FuelSource::new(10.0, 10.0).unwrap();

    assert!(fuel_source.is_full());

    fuel_source.set_fuel(0.0);
    assert!(!fuel_source.is_full());
}

#[test]
fn current_consumption_rate_and_set_consumption_rate_works() {
    let mut fuel_source = FuelSource::new(10.0, 10.0).unwrap();

    assert_eq!(fuel_source.current_consumption_rate(), 0.0);

    fuel_source.set_current_consumption_rate(1.0);
    assert_eq!(fuel_source.current_consumption_rate(), 1.0);
}

#[test]
fn add_fuel_works() {
    let mut fuel_source = FuelSource::new(1.0, 0.0).unwrap();

    assert_eq!(fuel_source.current_capacity(), 0.0);

    fuel_source.add_fuel(1.0);
    assert_eq!(fuel_source.current_capacity(), 1.0);
}

#[test]
fn set_fuel_works() {
    let mut fuel_source = FuelSource::new(10.0, 10.0).unwrap();

    assert_eq!(fuel_source.current_capacity(), 10.0);

    fuel_source.set_fuel(5.0);
    assert_eq!(fuel_source.current_capacity(), 5.0);
}

#[test]
fn set_fuel_rejects_negative_numbers() {
    let mut fuel_source = FuelSource::new(10.0, 10.0).unwrap();

    assert!(!fuel_source.set_fuel(-1.0));
}

#[test]
fn set_fuel_rejects_non_finite_numbers() {
    let mut fuel_source = FuelSource::new(10.0, 10.0).unwrap();

    assert!(!fuel_source.set_fuel(f32::INFINITY));
    assert!(!fuel_source.set_fuel(f32::NEG_INFINITY));
    assert!(!fuel_source.set_fuel(f32::NAN));
}

#[test]
fn consume_works() {
    let mut fuel_source = FuelSource::new(10.0, 10.0).unwrap();

    assert_eq!(fuel_source.current_capacity(), 10.0);

    fuel_source.set_current_consumption_rate(1.0);
    let consumed = fuel_source.consume();
    assert!(consumed);
    assert_eq!(fuel_source.current_capacity(), 9.0);
}

#[test]
fn can_consume_works() {
    let mut fuel_source = FuelSource::new(10.0, 10.0).unwrap();

    fuel_source.set_current_consumption_rate(1.0);
    assert!(fuel_source.can_consume());

    fuel_source.set_fuel(0.0);
    assert!(!fuel_source.can_consume());
}