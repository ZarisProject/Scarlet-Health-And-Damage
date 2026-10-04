# Scarlet Health & Damage

An UE5 plugin containing health and damage systems, originally developed for Zaris.

**Status: In Development**

---
### Health
**HP (Health Points)** is a floating point value that represents the amount of health the entity possesses. This value is capped in a range of 0.0 to **Max HP**. When **HP** value reaches zero a `HealthDepleted` event is triggered.

*For `SHD_RHealthComponent`:*
When **HP** value is decreased a *Regeneration Timer* is started. Once that timer finishes it's count down, passive regeneration starts to occur. Every tick during the passive regeneration the following modification to **HP** is applied:
$$
HP := HP + RegeneratationRate \cdot \Delta t.
$$
### Damage
User can register as many **Damage Types** as their project requires. Each application of damage has exactly one **Damage Type**. For attacks with multiple damage types damage is applied separately for every type.

Every entity capable of receiving damage has an associated *Damage Scaling Map* - a `TMap` that matches every damage type to a `float` value, that represents this entity's affinity to the given damage type. This value is called *Damage Scale*. *Damage Scale* less than 1.0 depicts resistance to the damage type and *Damage Scaling* greater than 1.0 - vulnerability to it. If damage type is not present in the *Damage Scaling Map*, then it's scale is assumed to be 1.0.

---
### Implementation

![](Documentation/Code%20Design.png)