# Husarion ROS2 Learning Progress

Repository: ros2-roadmap-ultralab
Goal: Track applied ROS2 system understanding using Husarion tutorials with ros2 docs for reference . 

---

# 1. ROS2 Introduction

## Concepts

* [ ] ROS2 architecture overview
* [ ] Nodes
* [ ] Topics
* [ ] Publishers vs Subscribers
* [ ] ROS2 workspace structure
* [ ] Packages and dependencies

## Practical

* [ ] Install and configure ROS2 workspace
* [ ] Run demo nodes
* [ ] Inspect nodes with `ros2 node list`
* [ ] Inspect topics with `ros2 topic list`
* [ ] Echo topic data

## Understanding Check

* [ ] Explain ROS graph architecture
* [ ] Explain publish–subscribe model

---

# 2. Creating Nodes and Messages

## Concepts

* [ ] ROS2 node lifecycle
* [ ] Message types
* [ ] Custom messages

## Practical

* [ ] Create Python ROS2 package
* [ ] Create first node
* [ ] Implement publisher node
* [ ] Implement subscriber node
* [ ] Create custom message type
* [ ] Build workspace with `colcon`

## Understanding Check

* [ ] Explain message serialization
* [ ] Explain topic data flow

---

# 3. Creating Nodes with Services

## Concepts

* [ ] Services vs topics
* [ ] Request–response model

## Practical

* [ ] Create service node
* [ ] Create service client
* [ ] Test service interaction
* [ ] Inspect services with CLI tools

## Understanding Check

* [ ] Explain when to use services instead of topics

---

# 4. Kinematics and Visualization

## Concepts

* [ ] Differential drive kinematics
* [ ] Robot motion equations
* [ ] Robot coordinate frames

## Practical

* [ ] Visualize robot model in RViz
* [ ] Run robot simulation
* [ ] Observe odometry output

## Understanding Check

* [ ] Explain how wheel velocity translates to robot motion

---

# 5. OpenCV Tracking

## Concepts

* [ ] Image processing in robotics
* [ ] Camera data streams
* [ ] Object tracking basics

## Practical

* [ ] Subscribe to camera image topic
* [ ] Process image with OpenCV
* [ ] Implement object tracking
* [ ] Publish tracking result

## Understanding Check

* [ ] Explain camera → perception → control pipeline

---

# 6. Robot Network

## Concepts

* [ ] ROS2 distributed system model
* [ ] DDS discovery
* [ ] Multi-machine communication

## Practical

* [ ] Configure ROS domain ID
* [ ] Connect multiple machines
* [ ] Test node communication across network

## Understanding Check

* [ ] Explain DDS discovery process

---

# 7. Transformations

## Concepts

* [ ] Coordinate frames
* [ ] TF tree
* [ ] Static vs dynamic transforms

## Practical

* [ ] Inspect TF tree
* [ ] Publish transform
* [ ] Visualize transforms in RViz

## Understanding Check

* [ ] Explain how robot coordinate frames relate

---

# 8. SLAM

## Concepts

* [ ] Simultaneous Localization and Mapping
* [ ] Occupancy grid maps
* [ ] Sensor fusion

## Practical

* [ ] Launch SLAM system
* [ ] Generate map in simulation
* [ ] Save map

## Understanding Check

* [ ] Explain how SLAM builds a map

---

# 9. Navigation

## Concepts

* [ ] Navigation stack architecture
* [ ] Path planning
* [ ] Costmaps

## Practical

* [ ] Launch Nav2
* [ ] Load map
* [ ] Send navigation goal
* [ ] Observe path planning

## Understanding Check

* [ ] Explain global vs local planner

---

# 10. Exploration

## Concepts

* [ ] Autonomous exploration
* [ ] Frontier detection
* [ ] Exploration strategies

## Practical

* [ ] Launch exploration node
* [ ] Observe autonomous map expansion

## Understanding Check

* [ ] Explain frontier-based exploration

---

# Reflection

After each tutorial:

* [ ] What worked
* [ ] What broke
* [ ] Key insight learned
* [ ] Questions for deeper research

---
