#ifndef KINEMATICROBOTMODELKDL_HPP
#define KINEMATICROBOTMODELKDL_HPP

#include <kdl/tree.hpp>
#include "RobotModel.hpp"

namespace wbc{

class TaskFrameKDL;

/** The kinematic model describes the kinemetic relationships required for wbc. It is based on a single KDL Tree, although it is possible to add an arbitrary
 *  number of trees (e.g. for controlling multiple robots at the same time or to described robot-object relationships). Particularly, the kinematic contains
 *  the task frames (see TaskFrame.hpp for details), which are used to describe the control problem.
 */
class KinematicRobotModelKDL : public RobotModel{

    typedef std::map<std::string, int> JointIndexMap;

protected:
    KDL::Tree full_tree;
    JointIndexMap joint_index_map;

public:
    KinematicRobotModelKDL(const std::string& _base_frame = "");
    virtual ~KinematicRobotModelKDL(){}

    /**
     * @brief Load a model and add it to the overall robot model, e.g. another robot or an object attached to the robot. Within this
     *        implementation, the model will be represented as KDL tree.
     * @param RobotModelConfig Config of the robot model.
     *            - file: Has to be the full path of a URDF model file. Will be parsed into a KDL tree. If the overall tree
     *                    is empty (i.e. if loadModel is called for the first time), the overall tree will be equal to the new
     *                    tree afterwards. Otherwise the new tree will be attached to the overall tree.
     *            - hook: The KDL segment name to which the new tree will be attached. Can be left empty if loadModel() is called
     *                    for the first time
     *            - initial_pose: Initial pose of the new KDL tree with respect to the given hook frame. Will be ignored if loadModel()
     *                            is called for the first time
     */
    virtual bool loadModel(const RobotModelConfig& config);

    /**
     * @brief Update all task frames in the model with a new joint state and (optionally) new link states
     * @param joint_state The joint_state vector. Has to contain all joint names that are relevant to any task frame,
     *                    that means all joints that are contained in a kinematic chain between the robot base frame and
     *                    one of the task frames
     * @param poses The new link poses. The SourceFrame has to be the same as the segment name that is to be updated. Can be left empty,
     *              if no segmented are to be updated
     */
    virtual void update(const base::samples::Joints& joint_state,
                        const std::vector<base::samples::RigidBodyState>& poses = std::vector<base::samples::RigidBodyState>());

    /**
     * @brief Check if a frame is available in the model
     */
    bool hasFrame(const std::string &name);

protected:
    /**
     * @brief Add a task frame to the model (see TaskFrame.hpp for details about task frames)
     * @param tf_name Name of the task frame. Has to be a valid frame of the model. This method will try to create a kinematic
     *                chain between the robot base frame and the task frame.
     * @return True in case of success, false otherwise (e.g. if the task frame already exists)
     */
    virtual TaskFrame* createTaskFrame(const std::string &tf_name);
};

}

#endif // KINEMATICMODEL_HPP