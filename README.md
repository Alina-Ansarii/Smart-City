# Smart City Management System

A comprehensive C++ system for managing and integrating multiple city sectors including Transportation, Education, Medical, Commercial, Population, and Public Facilities.

## Quick Start

1. **Launch the Program**: Run `FINAL_PROJECT.exe`
2. **Load Data**: Select option `61` from the main menu to load CSV data files
3. **Explore Features**: Use the main menu to navigate through different modules and operations

## Main Menu Structure

### **Tier 1: Essential Functions (1-5)**
Quick access to the most important city operations:
- **Option 1**: Smart City Dashboard - Overview of all city systems
- **Option 2**: Emergency Response - Find emergency services by Citizen CNIC
- **Option 3**: Find All Nearest Facilities - Locate nearest facilities of all types
- **Option 4**: Generate Citizen Health Profile - View health information
- **Option 5**: Integrate School Transport - Manage school transportation

### **Tier 2: Advanced Functions (6-10)**
Cross-module analytics and planning:
- **Option 6**: Recommend Schools for Student
- **Option 7**: Generate City Planning Report
- **Option 8**: Find Nearest Pharmacy with Medicine
- **Option 9**: Analyze Sector Health Metrics
- **Option 10**: Plan Emergency Evacuation

### **Module-Specific Operations (11-61)**

#### **Transport Module (11-19)**
- Register companies and bus stops
- Manage buses and routes
- Find nearest stops and emergency routing

#### **Education Module (20-27)**
- Register schools, departments, and classes
- Manage students and subjects
- View rankings and statistics

#### **Medical Module (28-35)**
- View hospitals and pharmacies
- Check bed availability
- Register patients and doctors
- Search medicines

#### **Commercial Module (36-44)**
- Register malls and products
- Search by name or category
- View mall connectivity and statistics

#### **Population Module (45-51)**
- Manage city hierarchy (Sectors → Streets → Houses)
- Register citizens and search records
- View population statistics

#### **Full Module Demos (52-57)**
Run complete demonstrations of each module with sample data.

#### **Additional Operations (58-61)**
- **58**: Register Doctor
- **59**: Register Patient
- **60**: Connect Bus Stops
- **61**: Load Data from CSV Files

## CSV Files Format

Place these files in the same directory as the executable:

- **hospitals.csv**: HospitalID,Name,Sector,Latitude,Longitude
- **pharmacies.csv**: PharmacyID,Name,Sector,Latitude,Longitude
- **schools.csv**: SchoolID,Name,Sector,Latitude,Longitude,Rating
- **stops.csv**: StopID,Name,Location,Latitude,Longitude
- **buses.csv**: BusNumber,CompanyID,CompanyName,InitialStop,Capacity
- **population.csv**: CNIC,Name,Age,Gender,Occupation,Sector,Street,HouseNum

## Typical Workflow

1. Start the program and select **Option 61** to load initial data from CSV files
2. Use **Options 11-51** to manually register additional data or make changes
3. Use **Options 1-10** for cross-module queries and analysis
4. Use **Options 52-57** to see demonstrations of each module's capabilities
5. Select **Option 0** to exit

## Key Features

✓ **Multi-Sector Integration** - 6 interconnected city sectors
✓ **Geographic Search** - Find facilities by location coordinates
✓ **Emergency Response** - Quick access to critical services
✓ **Data Management** - Register, update, and search citizen records
✓ **Analytics** - Generate reports and statistics
✓ **Route Planning** - Find shortest paths and nearest facilities

---

**Note**: Remember to connect bus stops (Option 60) after loading transport data for route calculations to work properly.
